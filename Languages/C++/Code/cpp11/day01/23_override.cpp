#include <iostream>
using namespace std;

class A1
{
public:
    //这是第一个虚函数，没有重写，不能用override修饰
    virtual int func(int a)
    {

    }
};

class A2:public A1
{
public:
    //在重写虚函数地方，加上override, 要求重写的虚函数和基类一模一样
    virtual int func(int b) override
    {

    }
};


int main()
{



    return 0;
}
