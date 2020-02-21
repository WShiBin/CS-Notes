#include <iostream>

using namespace std;

// class AgeType = int
// 类模版才会有默认类型,函数模版没有
template <class NameType, class AgeType = int>
class Person
{
public:
    NameType name;
    AgeType age;
    Person(NameType name, AgeType age) : name(name), age(age) {}
};

int main(int argc, char *argv[])
{

    Person<string, int> p("shibin", 19);
    cout << p.name << "  --  " << p.age << endl;
    return 0;
}