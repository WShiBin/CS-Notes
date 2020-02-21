#include <iostream>
#include <string>

using namespace std;

class Person
{
public:
    string name;
    int age;
    Person() {}
    Person(string name, int age) : name(name), age(age)
    {
    }
    ~Person() {}
    Person operator+(Person &p)
    {
        Person tmp;
        tmp.name = this->name + p.name;
        tmp.age = this->age + p.age;
        return tmp;
    }
    Person operator+(int age)
    {
        Person tmp;
        tmp.name = this->name;
        tmp.age = this->age + age;
        return tmp;
    }
};

// Person operator+(Person &p1, Person &p2)
// {
//     Person tmp;
//     tmp.name = p1.name + p2.name;
//     tmp.age = p1.age + p2.age;
//     return tmp;
// }

int main(int argc, char *argv[])
{
    Person p1("shibin", 18);
    Person p2("shibin", 18);
    Person p3 = p1 + p2;
    // Person p3 = p1.operator+(p2);
    cout << p3.name << " " << p3.age << endl;

    Person p4 = p2 + 10;
    cout << p4.name << " " << p4.age << endl;
    return 0;
}