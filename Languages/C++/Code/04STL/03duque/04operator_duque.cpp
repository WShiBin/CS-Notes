#include <deque>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    deque<int> d;
    // push_back(elem);  //在容器尾部添加一个数据
    // push_front(elem); //在容器头部插入一个数据
    // pop_back();       //删除容器最后一个数据
    // pop_front();      //删除容器第一个数据
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);
    d.push_front(30);
    d.push_front(20);
    d.push_front(10);

    for (auto it = d.begin(); it != d.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // at(idx);    //返回索引idx所指的数据，如果idx越界，抛出out_of_range。
    cout << "get by at " << d.at(2) << endl;
    // operator[]; //返回索引idx所指的数据，如果idx越界，不抛出异常，直接出错。
    d[2] = 100;
    cout << "change by [] prerator " << d.at(2) << endl;
    // front();    //返回第一个数据。
    cout << "front = " << d.front() << endl;
    // back();     //返回最后一个数据
    cout << "back = " << d.back() << endl;

    // insert(pos, elem);     //在pos位置插入一个elem元素的拷贝，返回新数据的位置。
    // insert(pos, n, elem);  //在pos位置插入n个elem数据，无返回值。
    // insert(pos, beg, end); //在pos位置插入[beg,end)区间的数据，无返回值。

    // clear();         //移除容器的所有数据
    // erase(beg, end); //删除[beg,end)区间的数据，返回下一个数据的位置。
    // erase(pos);      //删除pos位置的数据，返回下一个数据的位置。

    return 0;
}