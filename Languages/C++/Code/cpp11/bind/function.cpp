#include <functional>
#include <iostream>
#include <string>

using namespace std;

void fun1()
{
    cout << "func1" << endl;
}

class P
{
public:
    static void func2(string msg)
    {
        cout << msg << endl;
    }
};
class Functor
{
public:
    void operator()(string msg)
    {
        cout << msg << endl;
    }
};

void func3(function<void(string)> fun, string msg)
{
    fun(msg);
}
void func4(string msg, function<void(string)> fun)
{
    fun(msg);
}

int main(int argc, char *argv[])
{
    // 普通函数
    function<void()> f = fun1;
    f();

    // 类静态函数
    function<void(string)> f2 = P::func2;
    f2("hello function");

    // 仿函数
    Functor functor;
    function<void(string)> f3 = functor;
    f3("hello functor");

    func3(f3, "hello from callback");

    func4("lambda", [](string msg) {
        cout << "msg = " << msg << endl;
    });

    return 0;
}