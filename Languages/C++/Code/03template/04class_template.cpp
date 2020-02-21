#include <iostream>

using namespace std;

template <class NameType, class AgeType>
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