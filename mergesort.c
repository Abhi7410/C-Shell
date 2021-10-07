#include "headers.h"

void merge(iiit arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    iiit L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].name,R[j].name)<=0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(iiit arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(iiit A[], int size,int flag)
{
    int i;
    if(flag == 0)
    {
        for (i = 0; i < size; i++)
            printf("[%d]  %s  %s  [%d] \n", A[i].jjn, A[i].state, A[i].name, A[i].ppd);
    }
    if (flag == 1)
    {
    for (i = 0; i < size; i++)
        if(strcmp(A[i].state,"Running")==0)
            printf("[%d]  %s  %s  [%d] \n", A[i].jjn, A[i].state, A[i].name, A[i].ppd);
    }
    if (flag == 2)
    {
        for (i = 0; i < size; i++)
            if (strcmp(A[i].state, "Stopped") == 0)
                printf("[%d]  %s  %s  [%d] \n", A[i].jjn, A[i].state, A[i].name, A[i].ppd);
    }
}