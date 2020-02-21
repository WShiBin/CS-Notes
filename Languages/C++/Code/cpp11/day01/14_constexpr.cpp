#include <iostream>
using namespace std;

int GetNum()
{
    return 3;
}

const int GetNum2()
{
    return 3;
}

constexpr int GetNum3()
{//常量表达式，发生在编译阶段
    return 3;
}

int main()
{
    //error: enumerator value for 'e1' is not an integer constant
    //枚举成员初始化，必须是整型常量
    //enum {e1=GetNum(), e2}; //枚举类型， err
    //enum {e1=GetNum2(), e2};//err

    enum {e1=GetNum3(), e2}; //ok

    constexpr int tmp = GetNum3(); //ok, 发生在编译阶段
    enum {a1 = tmp, a2};//ok

    return 0;
}
