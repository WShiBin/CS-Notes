#include <iostream>
#include <functional> //std::bind
using namespace std;
using namespace std::placeholders;

class Test
{
public:
    void func(int x, int y)
    {//成员函数
        cout << x << " " << y << endl;
    }

    int a; //成员变量
};

int main()
{
    Test obj; //创建对象

    //绑定成员函数
    function<void(int, int)> f1 = bind(&Test::func, &obj, _1, _2);
    f1(11, 22); //obj.func(11, 22)

    //绑定成员变量
    function<int &()> f2 = bind(&Test::a, &obj);
    f2() = 111; //obj.a = 111;
    cout << "obj.a = " << obj.a << endl;

    return 0;
}


