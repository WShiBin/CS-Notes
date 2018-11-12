#include <stdio.h>

void sort(int *arr, int len)
{
    for (int gap = len / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < len; i++)
        {
            int j;
            int temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
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