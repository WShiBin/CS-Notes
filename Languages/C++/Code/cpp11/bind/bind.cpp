#include <iostream>

using namespace std;

void func1(int a, int b)
{
    cout << "a = " << a << ", b = " << b << endl;
}

int func2(int a, int b)
{
    cout << "a = " << a << ", b = " << b << endl;
    return a + b;
}
int main(int argc, char *argv[])
{
    bind(func1, 10, 20)();

    bind(func2, std::placeholders::_1, std::placeholders::_2)(10, 20);

    bind(func2, placeholders::_1, placeholders::_2)(10, 30);
    bind(func2, placeholders::_2, placeholders::_2)(10, 30);
    // cout << bind(func2, 10, 20) << endl;

    return 0;
}