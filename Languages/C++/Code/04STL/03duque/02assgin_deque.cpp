#include <deque>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // assign(beg, end);                   //将[beg, end)区间中的数据拷贝赋值给本身。
    // assign(n, elem);                    //将n个elem拷贝赋值给本身。
    // deque &operator=(const deque &deq); //重载等号操作符
    // swap(deq);                          // 将deq与本身的元素互换

    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);

    deque<int> d2;
    // d2.assign(d.begin(), d.end());
    d2.assign(++d.begin(), d.end());

    for (auto &val : d2)
    {
        cout << val << endl;
    }
    cout << endl;

    deque<int> d3 = d2;

    d3.swap(d);
    for (auto &val : d)
    {
        cout << val << " ";
    }
    cout << endl;
    for (auto &val : d3)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}