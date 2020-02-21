#include <iostream>
using namespace std;

/*
constexpr函数的限制：
    函数中只能有一个return语句（有极少特例）
    函数必须返回值（不能是void函数）
    在使用前必须已有定义
    return返回语句表达式中不能使用非常量表达式的函数、全局数据，且必须是一个常量表达式
*/

#if 0
constexpr int func01()
{
    //err, 函数中只能有一个return语句
    constexpr int a = 1;
    return a;
}

//err, return返回语句表达式中不能使用非常量表达式的函数、全局数据，且必须是一个常量表达式
int a = 3;
constexpr int func03()
{
    return a; //返回全局数据
}

int test()
{
    return 10;
}

constexpr int func02()
{
    //err, 不能使用非常量表达式的函数
    return test();
}

#endif


int main()
{
    //声明
    constexpr int func02();
    constexpr int tmp = func02(); //err, 在使用前必须已有定义

    return 0;
}

constexpr int func02()
{
    //允许包含typedef, using指令，静态断言
    static_assert(1, "fail");

    return 3;
}
