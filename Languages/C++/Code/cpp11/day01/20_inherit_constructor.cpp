#include <iostream>
using namespace std;

//基类
class A
{
public:
    A(int x, int y)
    {
        a = x;
        b = y;
    }

protected:
    int a;
    int b;
};

//派生类
class B:public A
{
public:
#if 0
    //通过参数列表给基类构造函数传参
    B(int x, int y): A(x, y)
    {

    }
#endif
    //继承构造
    using A::A;

    void display()
    {
        cout << "a = " << a << ", b = " << b << endl;
    }

    //没有增加新的成员变量
    int tmp;
};

int main()
{
    //派生类对象
    B obj(10, 20);
    obj.display();



    return 0;
}
