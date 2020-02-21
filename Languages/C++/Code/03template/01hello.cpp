#include <iostream>

using namespace std;

void swapInt(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
void swapDouble(double &a, double &b)
{
    double tmp = a;
    a = b;
    b = tmp;
}

// 相同
// template <typename T>
template <class T>
void swapWithTemplate(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

//
template <class T>
void fun()
{
    cout << "func" << endl;
}

int main(int argc, char *argv[])
{
    string a = "hehe";
    string b = "xixi";
    swapWithTemplate(a, b);
    cout << "a = " << a << "  --  b = " << b << endl;

    // fun(); // err
    fun<int>(); // OK
    return 0;
}