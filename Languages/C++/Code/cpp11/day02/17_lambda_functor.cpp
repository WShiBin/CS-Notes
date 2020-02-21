#include <iostream>
using namespace std;

//仿函数，重载operator()
class MyFunctor
{
public:
    MyFunctor(int i): r(i) {} //构造函数

    //仿函数，重载operator()
    int operator() (int tmp)
    {
        return tmp+r;
    }

private:
    int r;
};

int main()
{
    int tmp = 10;

    //仿函数的调用
    MyFunctor obj(tmp); //调用构造函数

    //调用仿函数
    cout << "result1 = " << obj(1) << endl;

    //仿函数是编译器实现lambda的一种方式
    //lambda表达式
    auto f = [&](int t)
        {
            return tmp+t;
        };
    cout << "result2 = " << f(1) << endl;


    return 0;
}
