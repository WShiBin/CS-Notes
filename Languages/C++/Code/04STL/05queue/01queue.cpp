#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char *argv[])
{
    // queue<T> queT;                      //queue采用模板类实现，queue对象的默认构造形式：
    // queue(const queue &que);            //拷贝构造函数
    // queue &operator=(const queue &que); //重载等号操作符
    queue<int> q;
    queue<int> q2(q);
    queue<int> q3 = q2;

    // push(elem);                         //往队尾添加元素
    // pop();                              //从队头移除第一个元素
    q.push(10);
    q.push(20);
    q.push(30);
    q.push(40);

    q.pop(); // pop 10

    // back();                             //返回最后一个元素
    // front();                            //返回第一个元素
    cout << "back is " << q.back() << endl;
    cout << "front is " << q.front() << endl;

    // empty();                            //判断队列是否为空
    // size();                             //返回队列的大小
    cout << "is empty ? " << q.empty() << endl;
    cout << "size is " << q.size() << endl;

    return 0;
}