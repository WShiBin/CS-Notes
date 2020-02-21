#include <iostream>

using namespace std;
enum MyEnum : char
{
    A,
    B = 100,
    C,
    D,
    E = 10,
    F = 10,
};

enum class MyEnum1 : char
{
    A,
    B = 100,
    C,
};

// enum
// enum class
int main(int argc, char *argv[])
{
    // 不能修改
    // MyEnum::B = 10;

    if (MyEnum::E == MyEnum::F)
    {
        cout << " e == f " << endl;
    }

    if (MyEnum::B == 100)
    {
        cout << " == " << endl;
    }
    cout << "a = " << MyEnum::A << endl;
    cout << "b = " << MyEnum::B << endl;
    cout << "c = " << MyEnum::C << endl;

    // 加class之后不能和int比较
    // if (MyClass::A == 1)
    if (MyEnum1::A == MyEnum1::B)
    {
        cout << " == " << endl;
    }

    return 0;
}