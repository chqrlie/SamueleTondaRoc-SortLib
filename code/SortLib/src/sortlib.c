#include "sortlib.h"

#define BASE(i) ((base) + ((i) * size))

/*
    @brief support method for merge_sort_R
*/
void merge_supp (size_t low, size_t mid, size_t hig, void* base, size_t size, int (*compar)(const void*, const void*))
{
    // creating temp arrays and support variable
    size_t i = 0, i1 = 0, i2 = 0, n1 = low, n2 = mid + 1, len1 = n2 - low, len2 = hig - mid;
    void *temp = (void*) malloc (size * (len1 + len2));

    for (;i < len1 + len2; i++)
    {
        int cmp = i1 < len1 ? (i2 < len2 ? compar (BASE (n1 + i1), BASE (n2 + i2)) : -1) : 1;
        memcpy (((temp) + (i * size)), cmp == -1 ? BASE (n1 + i1) : BASE (n2 + i2), size);
        i1 += cmp == -1; i2 += cmp >= 0;
    }

    memcpy (BASE (low), temp, size * (len1 + len2));
    free (temp);
}

/*
    @brief recursive method for the merge sort
*/
void merge_sort_R (size_t low, size_t hig, void* base, size_t size, int (*compar)(const void*, const void*))
{
    if (low < hig) 
    {
        size_t mid = low + ((hig - low) / 2);
        merge_sort_R (low, mid, base, size, compar);
        merge_sort_R (mid + 1, hig, base, size, compar);
        merge_supp (low, mid, hig, base, size,  compar);
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
void merge_sort (void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
{	
	if (base && compar && nitems)
		merge_sort_R (0, nitems - 1, base, size, compar);
}

void swap (void *a, void *b, size_t size, void* temp)
{
    memcpy (temp, a, size);
    memcpy (a, b, size);
    memcpy (b, temp, size);
}

size_t split (int low, int hig, void* base, size_t size, int (*compar)(const void*, const void*), void* temp)
{
    int i = low - 1, j = low, mid = low + ((hig - low) / 2), pivot = hig;
    
    if (!((*compar)(BASE (low), BASE (mid)) + (*compar)(BASE (low), BASE (hig)))) swap (BASE (low), BASE (hig), size, temp);
    else if (!((*compar)(BASE (mid), BASE (low)) + (*compar)(BASE (mid), BASE (hig)))) swap (BASE (mid), BASE (hig), size, temp);

    while (j < hig)
    {
        if ((*compar)(BASE (j), BASE (pivot)) < 0) 
        {
            i++;
            swap (BASE (i), BASE (j), size, temp);
        }
        j++;
    }
    swap (BASE (i + 1), BASE (pivot), size, temp);
    pivot = i + 1;
    return pivot;
}

/*
    @brief recursive method for the quick sort
*/
void quick_sort_R (int low, int hig, void *base, size_t size, int (*compar)(const void*, const void*), void* temp)
{
    if (low < hig)
    {
        int pivot = split (low, hig, base, size, compar, temp);
        quick_sort_R (low, pivot - 1, base, size, compar, temp);
        quick_sort_R (pivot + 1, hig, base, size, compar, temp);
    }
}

/*
    @brief quick sort for any type of array
    @param base pointer to the first element of the arry
    @param nitems lenght of the array
    @param size size of array items
    @param compar compare function
    @warning needs a compare function such that if the first elem is "bigger" than the second it returns 1, if it's equal it ret 0, else -1
*/
void quick_sort (void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) 
{
    void *temp = (void*) malloc (size);
    if (base && compar && nitems)
        quick_sort_R (0, nitems - 1, base, size, compar, temp);
    free (temp);
}
