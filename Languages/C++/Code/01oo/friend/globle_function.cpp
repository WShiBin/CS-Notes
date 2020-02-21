#include <iostream>

using namespace std;

class Person
{
    friend void hehe();

public:
    string name;
    Person(string name, int age) : name(name), age(age)
    {
    }

private:
    int age;
};

void hehe()
{
    Person p("shibin", 18);
    cout << p.name << " " << p.age << endl;
}

int main(int argc, char *argv[])
{
    hehe();
    return 0;
}