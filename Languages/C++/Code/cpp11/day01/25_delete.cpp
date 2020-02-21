#include <iostream>
using namespace std;

class X
{
public:
    X() {} //普通无参
    X(const X &)=delete; //拷贝构造, 用"=delete"修饰，此函数被禁用
    X & operator=(const X &)=delete; //赋值运算符重载函数, 用"=delete"修饰，此函数被禁用

    X(int) =delete; //用"=delete"修饰，此函数被禁用

    void *operator new(size_t) =delete;
    void *operator new[](size_t) =delete;
};


int main()
{
    X obj1; //普通无参
    //X obj2 = obj1; //err, 拷贝构造被禁用

    //obj2 = obj1; //err, 赋值运算符重载函数被禁用

    //X obj3(10); //err,

    //X *p = new X; //err
    //X *p = new X[10]; //err


    return 0;
}
