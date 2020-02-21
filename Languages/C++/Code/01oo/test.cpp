#include <iostream>

using namespace std;
class Person
{
public:
    string name;
    int age;

    // 无参构造
    Person()
    {
    }

    // 有参构造
    Person(int age) : age(age)
    {
    }
    Person(string name);
    // : age(age)
    Person(string name, int age)
    {
        this->name = name;
        this->age = age;
    }
    // 拷贝构造
    Person(const Person &p)
    {
        age = p.age;
        name = p.name;
    }
    // 析构函数
    ~Person()
    {
    }
};
// Person::Person(string namestr) : name(namestr)
Person::Person(string namestr) : name{namestr}
{
    cout << "name " << name << endl;
}

int main(int argc, char *argv[])
{
    Person{"shibin"};
    return 0;
}
