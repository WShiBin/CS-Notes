#include <deque>
#include <iostream>

using namespace std;

// 没有容量
int main(int argc, char *argv[])
{
    // deque.size();            //返回容器中元素的个数
    // deque.empty();           //判断容器是否为空
    // deque.resize(num);       //重新指定容器的长度为num,若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
    // deque.resize(num, elem); //重新指定容器的长度为num,若容器变长，则以elem值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除
    deque<int> d;
    d.push_back(10);
    d.push_back(20);
    d.push_back(30);
    d.push_back(40);

    cout << "size = " << d.size() << endl;

    cout << d.empty() << endl;

    d.resize(3);

    for (auto &val : d)
    {
        cout << val << " ";
    }
    cout << endl;

    d.resize(10, 100);
    for (auto &val : d)
    {
        cout << val << " ";
    }

    cout << endl;

    return 0;
}