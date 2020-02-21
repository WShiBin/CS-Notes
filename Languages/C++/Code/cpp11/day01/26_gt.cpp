#include <iostream>
using namespace std;

template<int i> class X {};
template<class T> class Y {};

int main()
{
    Y<X<10>> obj1; //C++11之前，2个右尖括号之间必须有空格


    return 0;
}
