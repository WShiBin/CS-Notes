#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
    }

    cout << "capacity:" << v.capacity() << endl;
    cout << "size:" << v.size() << endl;

    //此时 通过resize改变容器大小
    v.resize(10);

    cout << "capacity:" << v.capacity() << endl;
    cout << "size:" << v.size() << endl;

    // 匿名变量只在当前行有效
    //容量没有改变
    vector<int>(v).swap(v);

    cout << "capacity:" << v.capacity() << endl;
    cout << "size:" << v.size() << endl;

    return 0;
}