#include <iostream>
using namespace std;

int main()
{
    int a = 10; //a为左值
    //int && b = a; //err, 左值不能绑定到右值引用

    int && c = std::move(a);    //std::move将一个左值转换为右值
    cout << "c = " << c << endl;

    return 0;
}

