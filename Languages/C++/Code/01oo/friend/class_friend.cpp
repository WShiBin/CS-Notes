#include <iostream>

using namespace std;

class B;
class A
{
    // 友元类, 要在前面声明
    friend class B;

public:
    string name;
    A()
    {
    }
    A(string name, int age) : name(name), age(age)
    {
    }

private:
    int age;
};
class B
{
public:
    A a;
    string name;
    B(string name, int age, A &a) : name(name), age(age)
    {
        this->a = a;
        cout << "a age " << a.age << endl;
    }

private:
    int age;
};

int main(int argc, char *argv[])
{

    return 0;
}