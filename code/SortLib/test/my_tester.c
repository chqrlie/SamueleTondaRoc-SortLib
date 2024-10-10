#include "../src/sortlib.h"
#include "support.h"

void merge_sort_test (void** base, size_t len, size_t size, int(*compar)(const void*, const void*), void(*print)(void** base, size_t len))
{
	(*print)(*base, len);
	merge_sort (base, len, size, compar);
	(*print)(*base, len);
	printf("\n");
	free(*base);
}

void quick_sort_test (void** base, size_t len, size_t size, int(*compar)(const void*, const void*), void(*print)(void** base, size_t len))
{
	(*print)(*base, len);
	quick_sort (base, len, size, compar);
	(*print)(*base, len);
	printf("\n");
	free(*base);
}

void test_suite()
{
	printf ("- MERGE SORT TEST -");

	// null array
	printf ("test [00] - NULL array pointer\n");
	merge_sort (NULL, 0, 0, (*cmp_int));

	// int array
	// empty arr	
	printf ("test [01] - empty int array\n");
	size_t len = 0;
	int *arr = create_int_arr (len);
	merge_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));	

	// size 1 arr
	printf ("test [02] - size 1 int array\n");
	len = 1;
	arr = create_int_arr (len);
	merge_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));

	// even size arr
	printf ("test [03] - even size int array\n");
	len = 20;
	arr = create_int_arr (len);
	merge_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));

	// odd size arr
	printf ("test [04] - odd size int array\n");
	len = 21;
	arr = create_int_arr (len);
	merge_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));
		
	// void cmp_func ptr
	printf ("test [05] - void cmp func ptr");
	len = 10;
	arr = create_int_arr (len);
	merge_sort_test ((void**) &arr, len, sizeof(int), NULL, (*prt_int_arr));

	// string array
	

	printf ("- QUICK SORT TEST -");

	// null array
	printf ("test [00] - NULL array pointer\n");
	quick_sort (NULL, 0, 0, (*cmp_int));

	// int array
	// empty arr	
	printf ("test [01] - empty int array\n");
	len = 0;
	arr = create_int_arr (len);
	quick_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));	

	// size 1 arr
	printf ("test [02] - size 1 int array\n");
	len = 1;
	arr = create_int_arr (len);
	quick_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));

	// even size arr
	printf ("test [03] - even size int array\n");
	len = 20;
	char *vec = create_char_arr (len);
	quick_sort_test ((void**) &vec, len, sizeof(char), (*cmp_char), (*prt_char_arr));

	// odd size arr
	printf ("test [04] - odd size int array\n");
	len = 7;
	arr = create_int_arr (len);
	quick_sort_test ((void**) &arr, len, sizeof(int), (*cmp_int), (*prt_int_arr));
		
	// void cmp_func ptr
	printf ("test [05] - void cmp func ptr");
	len = 10;
	arr = create_int_arr (len);
	quick_sort_test ((void**) &arr, len, sizeof(int), NULL, (*prt_int_arr));
}

int main ()
{
	test_suite();	
}
