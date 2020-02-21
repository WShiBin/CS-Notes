#include <iostream>

using namespace std;

template <class NameType, class AgeType>
class Person
{
public:
    NameType name;
    AgeType age;
    Person(NameType name, AgeType age) : name(name), age(age) {}
    void show()
    {
        cout << name << " - " << age << endl;
    }
};

// 方式一
void show1(Person<string, int> &p)
{
    p.show();
}

// 方式二
template <class T1, class T2>
void show2(Person<T1, T2> &p)
{
    p.show();
}

// 方式三
template <class T>
void show3(T &p)
{
    p.show();
}

int main(int argc, char *argv[])
{
    Person<string, int> p("shibin", 19);
    show1(p);
    show2(p);
    show3(p);

    return 0;
}