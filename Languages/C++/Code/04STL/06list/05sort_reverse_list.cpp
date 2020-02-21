#include <iostream>
#include <list>

using namespace std;

int main(int argc, char *argv[])
{
    // reverse(); //反转链表，比如lst包含1,3,5元素，运行此方法后，lst就包含5,3,1元素。
    // sort();    //list排序

    list<int> l;
    l.push_back(10);
    l.push_front(100);
    l.push_back(30);
    l.push_back(40);
    l.push_back(20);

    // sort(l.begin(), l.end()); // error
    // l.sort(); // 默认升序
    l.sort([](int a, int b) { return a < b; }); // 降序
    for (auto &val : l)
        cout
            << val << " ";
    cout << endl;

    l.reverse();

    for (auto &val : l)
        cout << val << " ";
    cout << endl;
    return 0;
}