#include <iostream>
#include <functional> //std::function
using namespace std;

//1、普通函数
void func()
{
    cout << __func__ << endl;
}

//2、类中静态函数
class Test
{
public:
    static int test_func(int a)
    {
        cout << __func__ << "(" << a << ") ->: ";
        return a;
    }
};

//3、类中的仿函数
class MyFunctor
{
public:
    int operator()(int a)
    {
        cout << __func__ << "(" << a << ") ->: ";
        return a;
    }
};

int main()
{
    //1、绑定普通函数
    function<void(void)> f1 = func;
    f1(); //等价于 func()

    //2、绑定类中的静态函数
    function<int(int)> f2 = Test::test_func;
    cout << f2(10) << endl; // Test::test_func(10)

    //3、绑定类中的仿函数，绑定对象, 仿函数调用obj()
    MyFunctor obj;
    function<int(int)> f3 = obj;
    cout << f3(22) << endl;


    return 0;
}

