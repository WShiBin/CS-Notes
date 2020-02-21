#include <iostream>
using namespace std;

template <class T1, class T2>
class Person;

template <class T1, class T2>
void printPerson2(Person<T1, T2> p)
{
    cout << p.name << " - " << p.age << endl;
}

template <class T1, class T2>
class Person
{
    // 全局函数的类内实现
    friend void printPerson(Person<T1, T2> &p)
    {
        cout << p.name << " - " << p.age << endl;
    }
    // 全局函数的类外实现
    // 0.在函数声明处添加<>
    // 1.在内外前面实现
    // 2.把class声明放在前面 (找不到类)
    friend void printPerson2<>(Person<T1, T2> p);

public:
    T1 name;
    T2 age;
    Person(T1 t1, T2 t2)
    {
        name = t1;
        age = t2;
    }
};

int main(int argc, char *argv[])
{
    Person<string, int> p("shibin", 18);
    printPerson(p);
    printPerson2(p);

    return 0;
}