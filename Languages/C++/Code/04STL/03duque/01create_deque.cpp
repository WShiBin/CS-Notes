#include <deque>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // deque<T> deqT;           //默认构造形式
    // deque(beg, end);         //构造函数将[beg, end)区间中的元素拷贝给本身。
    // deque(n, elem);          //构造函数将n个elem拷贝给本身。
    // deque(const deque &deq); //拷贝构造函数。

    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);

    deque<int> d2(10, 100);
    deque<int> d3(d.begin(), d.end());
    deque<int> d4(d3);

    // const_iterator
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    

    // for (auto &val : d4)
    // {
    //     cout << val << endl;
    // }

    return 0;
}