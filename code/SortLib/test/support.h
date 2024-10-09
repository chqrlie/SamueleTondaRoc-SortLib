#ifndef SUPPORT
#define SUPPORT

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// create int array
int* create_int_arr (size_t len);

// print int array
void prt_int_arr (void** arr, size_t len);

// compare int
int cmp_int (const void* a, const void* b);

// create char array
char* create_char_arr (size_t len);

// print char array
void prt_char_arr (void** arr, size_t len);

// compare char
int cmp_char (const void* a, const void* b);

#endif
