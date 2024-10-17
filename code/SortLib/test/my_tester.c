#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>
#include "../src/sortlib.h"

// Comparison functions
int int_compare(const void *a, const void *b) 
{
	return *(int*)a < *(int*)b ? -1 : (*(int*)a == *(int*)a ? 0 : 1);
}

int char_compare(const void *a, const void *b) 
{
    return *(char*)a < *(char*)b ? -1 : (*(char*)a == *(char*)a ? 0 : 1);
}

int string_compare(const void *a, const void *b) 
{
	int cmp = strcmp(*(const char**)a, *(const char**)b);
    return cmp < 0 ? -1 : (cmp > 0 ? 1 : 0);
}

int float_compare(const void *a, const void *b) 
{
    return *(float*)a < *(float*)b ? -1 : (*(float*)a == *(float*)a ? 0 : 1);
}

int double_compare(const void *a, const void *b) 
{
    return *(double*)a < *(double*)b ? -1 : (*(double*)a == *(double*)a ? 0 : 1);
}

// Struct for testing
typedef struct {
    int id;
    char name[50];
} Person;

int struct_compare(const void *a, const void *b) 
{
	int cmp = strcmp(((const Person*)a) -> name, ((const Person*)b) -> name);
    return cmp < 0 ? -1 : (cmp > 0 ? 1 : 0);
}

// Helper function to check if array is sorted
int is_sorted(void *array, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
{
    for (size_t i = 1; i < nitems; i++)
        if (compar(((array) + ((i - 1) * size)), ((array) + ((i) * size))) > 0)
			return 0; // Not sorted
    return 1; // Sorted
}

// Test function
void run_tests() {
    // Array of integers
    int int_arr[] = {5, 2, 9, 1, 5, 6};
    size_t int_size = sizeof(int_arr) / sizeof(int_arr[0]);
    
    merge_sort(int_arr, int_size, sizeof(int), int_compare);
    assert(is_sorted(int_arr, int_size, sizeof(int), int_compare));
    
    quick_sort(int_arr, int_size, sizeof(int), int_compare);
    assert(is_sorted(int_arr, int_size, sizeof(int), int_compare));

    // Array of characters
    char char_arr[] = {'z', 'x', 'a', 'b', 'y'};
    size_t char_size = sizeof(char_arr) / sizeof(char_arr[0]);

    merge_sort(char_arr, char_size, sizeof(char), char_compare);
    assert(is_sorted(char_arr, char_size, sizeof(char), char_compare));

    quick_sort(char_arr, char_size, sizeof(char), char_compare);
    assert(is_sorted(char_arr, char_size, sizeof(char), char_compare));

    // Array of strings
    const char *str_arr[] = {"banana", "apple", "cherry", "date"};
    size_t str_size = sizeof(str_arr) / sizeof(str_arr[0]);

    merge_sort(str_arr, str_size, sizeof(char*), string_compare);
    assert(is_sorted(str_arr, str_size, sizeof(char*), string_compare));

    quick_sort(str_arr, str_size, sizeof(char*), string_compare);
    assert(is_sorted(str_arr, str_size, sizeof(char*), string_compare));

    // Array of floats
    float float_arr[] = {2.5f, 1.5f, 4.0f, 3.0f};
    size_t float_size = sizeof(float_arr) / sizeof(float_arr[0]);

    merge_sort(float_arr, float_size, sizeof(float), float_compare);
    assert(is_sorted(float_arr, float_size, sizeof(float), float_compare));

    quick_sort(float_arr, float_size, sizeof(float), float_compare);
    assert(is_sorted(float_arr, float_size, sizeof(float), float_compare));

    // Array of doubles
    double double_arr[] = {2.5, 1.5, 4.0, 3.0};
    size_t double_size = sizeof(double_arr) / sizeof(double_arr[0]);

    merge_sort(double_arr, double_size, sizeof(double), double_compare);
    assert(is_sorted(double_arr, double_size, sizeof(double), double_compare));

    quick_sort(double_arr, double_size, sizeof(double), double_compare);
    assert(is_sorted(double_arr, double_size, sizeof(double), double_compare));

    // Array of structs
    Person people[] = { {1, "Charlie"}, {2, "Alice"}, {3, "Bob"} };
    size_t people_size = sizeof(people) / sizeof(people[0]);

    merge_sort(people, people_size, sizeof(Person), struct_compare);	
    assert(is_sorted(people, people_size, sizeof(Person), struct_compare));

    quick_sort(people, people_size, sizeof(Person), struct_compare);
    assert(is_sorted(people, people_size, sizeof(Person), struct_compare));

    // Edge cases
    // NULL array pointer
    merge_sort(NULL, int_size, sizeof(int), int_compare); // Should not crash
    quick_sort(NULL, int_size, sizeof(int), int_compare); // Should not crash

    // NULL compare function pointer
    merge_sort(int_arr, int_size, sizeof(int), NULL); // Should not crash
    quick_sort(int_arr, int_size, sizeof(int), NULL); // Should not crash

    // Invalid size
    merge_sort(int_arr, int_size, 0, int_compare); // Should not crash
    quick_sort(int_arr, int_size, 0, int_compare); // Should not crash
}

int main() {
    run_tests();
    printf("All tests passed!\n");
    return 0;
}
