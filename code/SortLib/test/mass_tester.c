#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../src/sortlib.h"

#define MAX_STR   100
#define LINE_SIZE 100

typedef struct Record {
	char line[LINE_SIZE];
	int id;
	char field1[MAX_STR];
	int field2;
	float field3;
} Record;

int show_timings = 1;

clock_t start_timing(const char *msg)
{
    if (show_timings && msg && *msg) {
        printf("%16s...", msg);
        fflush(stdout);
    }
    return clock();
}

void stop_timing(clock_t start)
{
    if (show_timings) {
        clock_t end = clock();
        double algo_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf(" complete: %.3fsec\n", algo_time);
    }
}

size_t calc_csvFile_len(FILE *file)
{
    clock_t start = start_timing("counting records");

    char buf[LINE_SIZE];
	size_t len = 0;

    while (fgets(buf, sizeof buf, file))
        len++;

    stop_timing(start);

	return len;
}

size_t gather_data(FILE *infile, Record *data, size_t len)
{
    clock_t start = start_timing("reading records");

    size_t rec = 0;  // number of records read

    for (size_t i = 0; i < len; i++) {
        int id, field2;
        char field1[MAX_STR];
        float field3;
        char eol[2];

        if (!fgets(data[rec].line, sizeof data[rec].line, infile)) {
            fprintf(stderr, "cannot read line %zu\n", i + 1);
            break;
        }
        if (sscanf(data[rec].line, "%d,%99[^,],%d,%f%1[\n]", &id, field1, &field2, &field3, eol) != 5) {
            fprintf(stderr, "invalid format line %zu: %s\n", i + 1, data[rec].line);
        } else {
            data[rec].id = id;
            strcpy(data[rec].field1, field1);
            data[rec].field2 = field2;
            data[rec].field3 = field3;
            rec++;
        }
	}

    stop_timing(start);
    return rec;
}

int write_data(FILE *outfile, Record *data, size_t len)
{
    clock_t start = start_timing("writing records");

    for (size_t i = 0; i < len; i++) {
		fputs(data[i].line, outfile);
	}
    if (fflush(outfile)) {
        fprintf(stderr, "error writing output file: %s\n", strerror(errno));
        return 1;
    }

    stop_timing(start);
    return 0;
}

int cmp_field1(const void *a, const void *b)
{
    const Record *ap = (const Record *)a;
    const Record *bp = (const Record *)b;
    return strcmp(ap->field1, bp->field1);
}

int cmp_field2(const void *a, const void *b)
{
    const Record *ap = (const Record *)a;
    const Record *bp = (const Record *)b;
    return ap->field2 < bp->field2 ? -1 :
        ap->field2 > bp->field2 ? 1 : 0;
}

int cmp_field3 (const void *a, const void *b)
{
    const Record *ap = (const Record *)a;
    const Record *bp = (const Record *)b;
    return ap->field3 < bp->field3 ? -1 :
        ap->field3 > bp->field3 ? 1 : 0;
}

// Helper function to check if array is sorted
int is_sorted(const void *array, size_t nitems, size_t size, int (*compar)(const void *, const void *))
{
    const unsigned char *p = (const unsigned char *)array;
    for (size_t i = 1; i < nitems; i++, p += size) {
        if (compar((const void *)p, (const void *)(p + size)) > 0)
            return 0; // Not sorted
    }
    return 1; // Sorted
}

int sort_records(FILE *infile, FILE *outfile, int field, int algo)
{
    // get the header line (if any)
    char header[LINE_SIZE];
    if (!fgets(header, sizeof header, infile)) {
        fprintf(stderr, "empty file\n");
        return 1;
    }
    if (*header >= '0' && *header <= '9') {
        // missing header line
        *header = '\0';
        fseek(infile, 0L, SEEK_SET);
    }

	// preparing the array
	size_t len = calc_csvFile_len(infile);
    Record *data = (Record *)calloc(sizeof(Record), len);
    if (data == NULL) {
        fprintf(stderr, "cannot allocate line array for %zu records\n", len);
        return 1;
    }

    // rewind the file pointer back to beginning of file
	fseek(infile, 0L, SEEK_SET);
    // re-read the header if any
    if (*header) {
        fgets(header, sizeof header, infile);
    }

	// filling the array with data from file
    size_t count = gather_data(infile, data, len);

	// defining compare func
    int (*cmp_func)(const void *, const void *) = NULL;
    switch (field) {
    case 1:
        cmp_func = cmp_field1;
        break;
    case 2:
        cmp_func = cmp_field2;
        break;
    case 3:
        cmp_func = cmp_field3;
        break;
    default:
        fprintf(stderr, "invalid sort field %d\n", field);
        return 1;
    }

	clock_t start = start_timing("sorting records");

    // chosing sorting algorithm
    if (algo == 1)
        merge_sort(data, count, sizeof(Record), cmp_func);
    else
        quick_sort(data, count, sizeof(Record), cmp_func);

    if (is_sorted(data, count, sizeof(Record), cmp_func)) {
        stop_timing(start);
        if (*header)
            fputs(header, outfile);
        // dumping the array data in an output file
        int status = write_data(outfile, data, count);
        free(data);
        return status;
    } else {
        fprintf(stderr, "array sorting failure\n");
        free(data);
        return 1;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "usage: ./mass_tester input-csv output-csv field algorithm\n"
                "  field: 1,2,3\n"
                "  algorithm: 1,2\n"
                );
        return 1;
    }

	// check command line arguments
	char *in_file_path = argv[1];
	char *out_file_path = argv[2];

    int field = atoi(argv[3]);
    if (field < 1 || field > 3) {
        fprintf(stderr, "invalid field '%s': must be in range 1..3\n", argv[3]);
        return 1;
    }
    int algo = atoi(argv[4]);
    if (algo < 1 || algo > 2) {
        fprintf(stderr, "invalid algorithm '%s': must be in range 1..2\n", argv[4]);
        return 1;
    }

	// open files
    FILE *infile = fopen(in_file_path, "r");
    if (infile == NULL) {
        fprintf(stderr, "cannot open %s: %s\n", in_file_path, strerror(errno));
        return 1;
    }

    FILE *outfile = fopen(out_file_path, "w");
    if (outfile == NULL) {
        fprintf(stderr, "cannot open %s: %s\n", out_file_path, strerror(errno));
        return 1;
    }

	// launch sorter
    int status = sort_records(infile, outfile, field, algo);
    fclose(infile);
    fclose(outfile);

	return status;
}
