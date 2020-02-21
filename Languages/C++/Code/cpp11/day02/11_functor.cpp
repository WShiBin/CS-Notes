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
    MyFunctor obj(10); //调用构造函数

    //调用仿函数
    cout << "result = " << obj(1) << endl;

    return 0;
}

