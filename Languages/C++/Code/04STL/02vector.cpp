#include <iostream>
#include <vector>

using namespace std;

template <class T>
void printVector(vector<T> v)
{
    // for (int stat = v.begin();)
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    // vector<T> v;                //采用模板实现类实现，默认构造函数
    // vector(v.begin(), v.end()); //将v[begin(), end())区间中的元素拷贝给本身。
    // vector(n, elem);            //构造函数将n个elem拷贝给本身。
    // vector(const vector &vec);  //拷贝构造函数。

    //例子 使用第二个构造函数 我们可以...
    int arr[] = {2, 3, 4, 1, 9};
    vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));
    vector<int> v2(v1.begin(), v1.end());
    vector<int> v3(10, 100);
    vector<int> v4(v3);

    printVector(v1);
    printVector(v2);
    printVector(v3);
    printVector(v4);

    return 0;
}