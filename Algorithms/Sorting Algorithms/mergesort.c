#include <stdio.h>

void merge(int *arr, int l, int m, int r)
{
    int i, j, index;
    int len_l = m - l + 1;
    int len_r = r - m;
    int arr_l[len_l], arr_r[len_r];

    // 1.把 arr 数据分别拷贝到 arr_l和arr_r
    for (i = 0; i < len_l; i++)
    {
        arr_l[i] = arr[l + i];
    }
    for (j = 0; j < len_r; j++)
    {
        arr_r[j] = arr[m + 1 + j];
    }

    // 2.比较arr_l 和 arr_r中的元素，存放到 arr 中
    i = 0, j = 0, index = l;
    while (i < len_l && j < len_r)
    {
        if (arr_l[i] <= arr_r[j])
        {
            arr[index] = arr_l[i];
            i++;
        }
        else
        {
            arr[index] = arr_r[j];
            j++;
        }
        index++;
    }

    // 3.把arr_l或者 arr_r 中剩下的数据拷贝到 arr 中
    while (i < len_l)
    {
        arr[index] = arr_l[i];
        index++;
        i++;
    }

    while (j < len_r)
    {
        arr[index] = arr_r[j];
        index++;
        j++;
    }
}

void sort(int *arr, int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        sort(arr, l, mid);
        sort(arr, mid + 1, r);

        merge(arr, l, mid, r);
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
    sort(arr, 0, len - 1);
    printArr(arr, len);
    return 0;
}