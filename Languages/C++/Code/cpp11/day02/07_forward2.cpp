#include <iostream>
using namespace std;

template<class T> void func(const T &)
{
    cout << "const T &" << endl;
}

template<class T> void func(T &)
{
    cout << "T &" << endl;
}

template<class T> void func(T &&)
{
    cout << "T &&" << endl;
}


template<class T> void forward_val(T &&tmp) //参数为右值引用
{
    //std::forward保存参数的左值、右值属性
    func( std::forward<T>(tmp) ); //定义
}

int main()
{
    int a = 0;
    const int &b = 1;

    //需要给forward_val()重载2个版本， const T &， T &
    forward_val(a); //"T &"
    forward_val(b);//const T &
    forward_val(111);//T &&


    return 0;
}


