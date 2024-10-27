#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void usage(void) {
    printf("usage: gen_rand_csv -n nb_lines [-s seed]\n");
    exit(1);
}

int main(int argc, char *argv[]) {
    long i, nb_lines = 1000000;
    int ch;

    while ((ch = getopt(argc, argv, "n:s:")) != -1) {
        switch (ch) {
        case 'n':
            nb_lines = strtol(optarg, NULL, 0);
            break;
        case 's':
            srand((unsigned)strtol(optarg, NULL, 0));
            break;
        case '?':
        default:
            usage();
        }
    }
    if (optind < argc)
        usage();

    printf("id,field1,field2,field3\n");
    for (i = 1; i <= nb_lines; i++) {
        int r = rand();
        printf("%ld,str-%d,%d,%.2f\n", i, r, r, r / 100.0);
    }
    return 0;
}
