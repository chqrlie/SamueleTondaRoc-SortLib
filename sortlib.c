#include "sortlib.h"

/*
    @brief support method for merge_sort_R
*/
void merge_supp (size_t low, size_t mid, size_t hig, void** base, int (*compar)(const void*, const void*))
{
    // creating temp arrays and support variables
    size_t n1 = low, n2 = mid + 1, len1 = n2 - low, len2 = hig - mid;
    void *temp1[len1], *temp2[len2];

    // filling temp arrays
    for (size_t i = 0; i < len1; i++){ temp1[i] = base[n1 + i]; printf ("%d ", temp1[i]);} printf("\n");
    for (size_t i = 0; i < len2; i++){ temp2[i] = base[n2 + i]; printf ("%d ", temp2[i]);} printf("\n");

    // sorting into original array
    size_t i = 0, i1 = 0, i2 = 0;
    while (i < len1 + len2)
    {
        int cmp = i1 < len1 ? (i2 < len2 ? compar (temp1[i1], temp2[i2]) : -1) : 1; // define cmp
        base[low + i] = cmp == 1 ? temp2[i2] : temp1[i1];   // place the lesser value in base
        i1 += cmp == -1; i2 += cmp >= 0; i++;   // updating indexes
    }
}

/*
    @brief recursive method for the merge sort
*/
void merge_sort_R (size_t low, size_t hig, void** base, size_t size, int (*compar)(const void*, const void*))
{
    if (low < hig) 
    {
        size_t mid = low + ((hig - low) / 2);
        merge_sort_R (low, mid, base, size, compar);
        merge_sort_R (mid + 1, hig, base, size, compar);
        merge_supp (low, mid, hig, base, compar);
    }
}

/*
    @brief merge sort for any type of array
    @param base pointer to the first element of the arry
    @param nitems lenght of the array
    @param size size of array items
    @param compar compare function
    @warning needs a compare function such that if the first elem is "bigger" than the second it returns 1, if it's equal it ret 0, else -1
*/
void merge_sort (void **base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
{
    merge_sort_R (0, nitems - 1, base, size, compar);
}

/*
    @brief recursive method for the quick sort
*/
void quick_sort_R ()
{

}

/*
    @brief quick sort for any type of array
    @param base pointer to the first element of the arry
    @param nitems lenght of the array
    @param size size of array items
    @param compar compare function
    @warning needs a compare function such that if the first elem is "bigger" than the second it returns 1, if it's equal it ret 0, else -1
*/
void quick_sort (void **base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
{

}
