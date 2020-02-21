#include <iostream>
using namespace std;

int main()
{
    int b = 10;
    auto f2 = [&]()
            {
                b = 111;
                cout << b << endl;
            };
    f2();
    cout << "b = " << b << endl;

    return 0;
}

int main01()
{
    int a = 10;
    //lambda表达式，新建一个变量，外部变量给这个变赋值一份， 值传递
    auto f1 = [=]() mutable
            {
                //a = 111;
                cout << "a = " << a << endl;
            };
    f1();

    cout << "a2 = " << a << endl;

    a = 222;
    f1();

    return 0;
}

