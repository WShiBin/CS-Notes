#include <iostream>

using namespace std;

class Person
{
public:
    string name;
    int age;
    Person(string name, int age) : name(name), age(age)
    {
    }

    // 前置++
    Person &operator++()
    {
        age++;
        return *this;
    }

    // 后置++
    Person &operator++(int)
    {
        Person tmp = *this;
        age++;
        return tmp;
    }
};

ostream &operator<<(ostream &cout, Person &p)
{
    cout << p.name << " " << p.age << endl;
    return cout;
}

int main(int argc, char *argv[])
{
    Person p("shibin", 19);
    // cout << ++p << endl;
    cout << p++ << endl;
    cout << p << endl;
    // cout << p;
    // p++

    return 0;
}