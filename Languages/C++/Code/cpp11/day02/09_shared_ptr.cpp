#include <iostream>
#include <memory> //智能指针头文件
using namespace std;

int main()
{
    shared_ptr<int> sp1(new int(11));
    shared_ptr<int> sp2 = sp1; //拷贝构造， 有2个对象和堆区空间绑定

    cout << "num = " << sp2.use_count() << endl; //打印计数器

    //释放sp1， 只是计数器减去1， 堆区空间没有释放
    sp1.reset();
    cout << "num = " << sp2.use_count() << endl; //打印计数器

    cout << *sp2 << endl;
    //cout << *sp1 << endl;//err， 释放sp1和堆区空间的绑定，无法通过sp1操作堆区内容

    //释放sp2， 只是计数器减去1， 当计数器的值为0， 堆区空间就是释放
    sp2.reset();
    cout << "num = " << sp2.use_count() << endl; //打印计数器

    return 0;
}
