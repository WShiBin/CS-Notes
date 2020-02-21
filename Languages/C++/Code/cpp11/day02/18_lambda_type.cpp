#include <iostream>
#include <functional>
using namespace std;


int main()
{
    int a = 10;

    function<int(int)> f1 = [](int a){ return a+1; };
    cout << f1(9) << endl;

    function<int(int)> f2 = bind(
        [](int a){ return a+1; },
        std::placeholders::_1
    );
    cout << f2(9) << endl;

    auto f4 = [](int x, int y) -> int { return x + y; };
    cout << f4(1, 2) << endl;

    decltype (f4) tmp = f4;
    cout << tmp(2, 2) << endl;

    //定义一个函数指针类型
    typedef int (*PFUC)(int, int);
    PFUC p1 = f4; //lambda表达式转换为函数指针， ok， lambda表达式不允许捕获外部变量
    cout << p1(10, 10) << endl;

    //decltype (f4) = p1; //函数指针转换为lambda表达式，这是不可以的




    return 0;
}
