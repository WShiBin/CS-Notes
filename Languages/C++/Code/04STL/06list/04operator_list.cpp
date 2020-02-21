#include <iostream>
#include <list>

using namespace std;

int main(int argc, char *argv[])
{
    list<int> l;
    // push_back(elem);       //在容器尾部加入一个元素
    // pop_back();            //删除容器中最后一个元素
    // push_front(elem);      //在容器开头插入一个元素
    // pop_front();           //从容器开头移除第一个元素
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l.push_front(100);
    l.pop_back();
    l.pop_front();

    list<int> l2(l);

    for (auto &val : l)
    {
        cout << val << " ";
    }
    cout << endl;

    // insert(pos, elem);     //在pos位置插elem元素的拷贝，返回新数据的位置。
    // insert(pos, n, elem);  //在pos位置插入n个elem数据，无返回值。
    // insert(pos, beg, end); //在pos位置插入[beg,end)区间的数据，无返回值。
    l.insert(++l.begin(), 1000);
    l.insert(++l.end(), 10, 100);
    l.insert(++l.begin(), l2.begin(), l2.end());
    for (auto &val : l)
    {
        cout << val << " ";
    }
    cout << endl;

    // clear();               //移除容器的所有数据
    // erase(beg, end);       //删除[beg,end)区间的数据，返回下一个数据的位置。
    // erase(pos);            //删除pos位置的数据，返回下一个数据的位置。
    // remove(elem);          //删除容器中所有与elem值匹配的元素。

    l.erase(++l.begin(), --l.end());
    // l.erase(l.begin());
    // l.clear();
    for (auto &val : l)
        cout << val << " ";
    cout << endl;

    l.remove(100);
    for (auto &val : l)
        cout << val << " ";
    cout << endl;

    return 0;
}