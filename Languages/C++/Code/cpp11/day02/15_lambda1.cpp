#include <iostream>
using namespace std;

int tmp = 1;

class Test
{
public:
    int i = 0;

    void func()
    {
        int a = 10;
        //err, []为空，没有捕获任何变量
        //auto f1 = [](){ cout << i << endl; };

        auto f1 = [=]() {
            cout << i << endl;
            cout << tmp << endl;
        };
        auto f2 = [&]() { cout << i << endl; };

        //只是捕获类成员变量、全局变量， 不能捕获局部变量
        auto f3 = [this]() {
            cout << i << endl;
            cout << tmp << endl;
            //cout << a << endl; //err
        };
    }
};

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;

    auto f1 = []() {};
    //a, b以值传递方式
    auto f2 = [a, b]() { cout << a << ", " << b << endl; };
    auto f3 = [a, b](int x, int y) {
        cout << a << ", " << b << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
    };
    //f3(10, 20);

    //以值传递方式传给lambda表达式
    auto f4 = [=] { cout << a << ", " << b << endl; };

    //以引用方式捕获外部的变量
    auto f5 = [&] { cout << a << ", " << b << endl; };

    //a以值传递， 其它以引用方式传递
    auto f6 = [&, a] { cout << a << ", " << b << endl; };

    //a以引用传递，其它值传递
    auto f7 = [=, &a] { cout << a << ", " << b << endl; };

    //默认情况下，lambda函数，以const修饰函数体， 值传递无法修改， 想修改加mutable
    auto f8 = [=]() mutable {
        a++;
        cout << tmp << endl;
    };

    return 0;
}
