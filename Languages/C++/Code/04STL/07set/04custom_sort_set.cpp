#include <iostream>
#include <set>

using namespace std;

class Person
{
public:
    string name;
    int age;
    Person(string name, int age) : name(name), age(age) {}
};

class MyCompare
{
public:
    // operator
    bool operator()(const Person &a, const Person &b)
    {
        return a.age > b.age;
    }
};

int main(int argc, char *argv[])
{
    set<Person, MyCompare> s;
    // Person p2("shibin", 18);
    // s.insert(p2);
    s.insert(Person("shibin", 14));
    s.insert(Person("shibin", 12));
    s.insert(Person("shibin", 12));
    s.insert(Person("shibin", 16));
    s.insert(Person("shibin", 18));
    s.insert(Person("shibin", 19));

    for (auto begin = s.begin(); begin != s.end(); ++begin)
    {
        cout << (*begin).name << " " << (*begin).age << endl;
    }
    cout << endl;

    return 0;
}