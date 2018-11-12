#include <stdio.h>

void sort(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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
    int arr[] = {4, 2, 8, 7, 0, 5, 6, 7, 1, 3, 9, 6};
    int len = sizeof(arr) / sizeof(arr[0]);
    sort(arr, len);
    printArr(arr, len);
    return 0;
}