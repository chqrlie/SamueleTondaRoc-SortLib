#include "support.h"
#include <time.h>

int* create_int_arr (size_t len)
{
	int* arr = (int*) malloc (len * sizeof(int));
	srand (time(NULL));
	for (size_t i = 0; i < len; i++) arr[i] = rand() % 100;
	// *(arr + (sizeof(int) * i)) = i;
	return arr;
}

void prt_int_arr (void** arr, size_t len)
{
	for (size_t i = 0; i < len; i++) printf ("%d ", *((int*) arr + i));
	printf("\n");
	// *((int*)(arr + (sizeof(int) * i)));
}

int cmp_int (const void* a,const void* b)
{
	int A = *(int*) a;
	int B = *(int*) b;
	return A < B ? -1 : (A == B ? 0 : 1);
}

char* create_char_arr (size_t len)
{
	char* arr = (char*) malloc (sizeof(char) * len);
	for (size_t i = 0; i < len; i++) arr[i] = 'z' - i;
	return arr;
}

void prt_char_arr (void** arr, size_t len)
{
	for (size_t i = 0; i < len; i++) 
		printf ("%c ", *((char*) arr + i));
	printf ("\n");
}

int cmp_char (const void* a, const void* b)
{
	char A = *(char*) a;
	char B = *(char*) b;
	return A < B ? -1 : (A == B ? 0 : 1);
}
