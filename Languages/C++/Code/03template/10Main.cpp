#include "10MyArray.hpp"
#include <iostream>

using namespace std;

template <class T>
void printArr(MyArray<T> &arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << endl;
    }
}

int main(int argc, char *argv[])
{
    MyArray<int> arr(10);
    MyArray<int> arr2(arr);
    MyArray<int> arr3(100);
    arr3 = arr;
    arr.pushBack(1);
    arr.pushBack(2);
    arr.pushBack(3);
    arr.pushBack(4);
    arr.pushBack(5);
    printArr(arr, arr.getSize());

    cout << "  --------------  " << endl;
    arr.deleteWithIndex(3);

    printArr(arr, arr.getSize());
    cout << "size " << arr.getSize() << endl;
    return 0;
}