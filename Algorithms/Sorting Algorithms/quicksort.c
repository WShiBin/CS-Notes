#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int low, int high)
{
    int pi = low;
    int pivot = arr[high];
    for (int i = low; i < high; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(&arr[i], &arr[pi]);
            pi++;
        }
    }
    swap(&arr[pi], &arr[high]);
    return pi;
}

void sort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        sort(arr, low, pi - 1);
        sort(arr, pi + 1, high);
    }
}

void printArr(int *arr, int len)
{
    for (int i = 0; i < len; i++)
        printf("%d\t", arr[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    int arr[] = {4, 2, 8, 0, 5, 7, 1, 3, 9, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    sort(arr, 0, len - 1);
    printArr(arr, len);
    return 0;
}