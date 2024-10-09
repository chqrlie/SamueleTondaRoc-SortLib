#include "support.h"
#include "../src/sortlib.h"

#define MAX_SIZE 100

typedef struct data_line {
	int id;
	char field1[MAX_SIZE];
	int field2;
	float field3;
} Line, *Line_ptr;

size_t calc_csvFile_len (FILE *file)
{
	size_t len = 0;
	printf ("calculating file lenght...\n");
	while (!feof(file))
	{
		
		char s[MAX_SIZE];
		fscanf (file, "%[^\n]\n", s);
		len++;
	}
	printf ("file lenght: %ld\n\n", len);

	fseek (file, 0L, SEEK_SET);
	return len;
}

void gather_data (FILE *infile, Line_ptr *data)
{
	int id, field2;
	char field1[MAX_SIZE];
	float field3;

	printf ("reading data...\n");
	for (size_t i = 0; !feof (infile); i++)
	{
		fscanf (infile, "%d,%[^,],%d,%f\n", &id, field1, &field2, &field3);
		(*data)[i].id = id;
		strcpy ((*data)[i].field1, field1);
		(*data)[i].field2 = field2;
		(*data)[i].field3 = field3;
	}
	fclose (infile);
	printf ("data loading complete!\n\n");
}

void write_data (FILE *outfile, Line_ptr *data, size_t len)
{
	printf ("writing data...\n");
	for (size_t i = 0; i < len; i++)
	{
		fprintf (outfile, "%d,%s,%d,%f\n", (*data)[i].id, (*data)[i].field1, (*data)[i].field2, (*data)[i].field3);
	}
	fclose (outfile);
	printf ("data writing complete!\n\n");
}

int cmp_field1 (const void* a, const void* b)
{
	char A[MAX_SIZE], B[MAX_SIZE];
	strcpy (A, ((Line_ptr) a) -> field1);
	strcpy (B, ((Line_ptr) b) -> field1);
	int cmp = strcmp (A, B);
	return cmp > 0 ? 1 : (cmp < 0 ? -1 : 0);
}

int cmp_field2 (const void* a, const void* b)
{
	int A = ((Line_ptr) a) -> field2;
	int B = ((Line_ptr) b) -> field2;
	return A < B ? -1 : (A == B ? 0 : 1);
}

int cmp_field3 (const void* a, const void* b)
{
	float A = ((Line_ptr) a) -> field3;
	float B = ((Line_ptr) b) -> field3;
	return A < B ? -1 : (A == B ? 0 : 1);
}

void sort_records (FILE *infile, FILE *outfile, size_t field, size_t algo)
{
	// preparing the array 
	size_t len = calc_csvFile_len (infile);
	Line_ptr data = (Line_ptr) malloc (sizeof(Line) * len);

	// filling the array with data from file
	gather_data (infile, &data);

	printf ("sorting...");
	// defining compare func
	int (*cmp_func)(const void*, const void*) = field == 1 ? (*cmp_field1) : (field == 2 ? (*cmp_field2) : (*cmp_field3));	

	// chosing sorting algorithm
	if (algo == 1) merge_sort ((void**) &data, len, sizeof(Line), cmp_func);
	else quick_sort ((void**) &data, len, sizeof(Line), cmp_func);
	printf ("array sorted!\n\n");

	// dumping the array data in an output file
	write_data(outfile, &data, len);
	free (data);
}

int main (int argc, char **argv)
{
	// reading command
	char* in_file_path = argv[1];
	char* out_file_path = argv[2];
	size_t field = (int) (*argv[3] - '0'),
			algo = (int) (*argv[4] - '0');

	// opening files (the closing happens in the gather_data and write_data methods)
	FILE *infile = NULL, *outfile = NULL;
	if (in_file_path) infile = fopen (in_file_path, "r");
	if (out_file_path) outfile = fopen (out_file_path, "w");

	// checking inputs and launching sorter
	if (infile && outfile && (field > 0 && field < 4) && (algo > 0 && algo < 3)) 
		sort_records (infile, outfile, field, algo);	
	else 
		printf("error in passed data: \"%s %s %s %ld %ld\"", argv[0], in_file_path, out_file_path, field, algo);	// info dump in case of error

	return 0;
}