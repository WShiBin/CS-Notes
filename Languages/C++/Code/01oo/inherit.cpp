#include <iostream>

using namespace std;

class X
{
public:
    int a;

protected:
    int b;

private:
    int c;
};

class PublicA : public X
{
public:
    void func()
    {
        a = 100;
        b = 100;
        // c = 100;
    }
};

class ProtectedB : protected X
{
public:
    void func()
    {
        a = 100;
        b = 100;
        // c = 100;
    }
};

class PrivateC : protected X
{
public:
    void func()
    {
        a = 100;
        b = 100;
        // c = 100;
    }
};
int main(int argc, char *argv[])
{
    PublicA a;
    a.a; // public
    // a.b; // protected
    // a.c;

    ProtectedB b;
    // b.a; // protected
    // b.b; // protected
    // b.c;

    PrivateC c;
    // c.a; // private
    // c.b; // private
    // c.c; //
    return 0;
}