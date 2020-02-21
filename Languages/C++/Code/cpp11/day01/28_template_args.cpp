#include <iostream>
using namespace std;

//1、普通函数的默认参数
void func(int a = 3) {}

//2、类模板支持默认的模板参数
template<class T, class T2=int> //类模板的模板参数必须是从右往左
class A
{

};

//3、C++11才支持，函数模板带默认的模板参数
//  函数模板的模板参数可以是从右往左，也可以是从左往右
template<class T=int, class T2> void func2(T a, T2 b){}


int main()
{



    return 0;
}
