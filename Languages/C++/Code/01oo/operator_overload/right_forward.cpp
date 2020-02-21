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
};

ostream &operator<<(ostream &cout, Person &p)
{
    cout << p.name << "  " << p.age << endl;
    return cout;
}
int main(int argc, char *argv[])
{
    Person p("shibin", 18);
    cout << p;
    // cout.operator<<(p);

    return 0;
}