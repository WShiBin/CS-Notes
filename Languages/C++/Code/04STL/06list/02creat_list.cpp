#include <iostream>
#include <list>

using namespace std;

int main(int argc, char *argv[])
{
    // list<T> lstT;          //list采用采用模板类实现,对象的默认构造形式：
    // list(beg, end);        //构造函数将[beg, end)区间中的元素拷贝给本身。
    // list(n, elem);         //构造函数将n个elem拷贝给本身。
    // list(const list &lst); //拷贝构造函数。
    list<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);

    list<int> l2(l.begin(), l.end());
    list<int> l3(10, 100);
    list<int> l4(l);

    return 0;
}