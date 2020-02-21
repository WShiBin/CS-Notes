#include <iostream>

using namespace std;

template <class T>
class Base
{
    T t;
};

class Son : public Base<int>
{
};

template <class T>
class Son2 : public Base<T>
{
};

template <class T1, class T2>
class Son3 : public Base<T1>
{
public:
    T2 m;
};

int main(int argc, char *argv[])
{

    Base<int> base;
    Son s;
    Son2<char> s2;
    Son3<char, int> s3;

    return 0;
}