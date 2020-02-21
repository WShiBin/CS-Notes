#include <iostream>

using namespace std;

class Person
{
public:
    Person() = default;
    Person(string name, int age) : m_Name(name), m_Age(age)
    {
    }

    Person(const Person &p) = default;

    ~Person() = default;

    Person operator=(const Person &p)
    {
    }

private:
    string m_Name;
    int m_Age;
};

int main(int argc, char *argv[])
{

    return 0;
}