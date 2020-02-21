#include <iostream>

using namespace std;

template <class T>
void swapwithtemplate(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <class T>
void sort(T *arr, int len)
{
    for (int i = 0; i < len; ++i)
    {
        int max = i;
        for (int j = i + 1; j < len; ++j)
        {
            if (arr[max] < arr[j])
            {
                max = j;
            }
        }

        if (max != i)
        {
            swapwithtemplate(arr[max], arr[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    // warning: ISO C++11 does not allow conversion from string literal to 'char *'
    // char *arr = "asdfghjkl";

    char arr[] = "asdfghjkl";

    int len = sizeof(arr) / sizeof(arr[0]);
    sort(arr, len);
    cout << arr << endl;
    return 0;
}