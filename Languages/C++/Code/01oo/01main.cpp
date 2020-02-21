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

int main(int argc, char *argv[])
{
    Person p;                // 元参构造
    Person p2("shibin", 18); // 构造函数
    Person p3(p2);           // 拷贝构造
    // Person p1();             // 这是一个函数声明

    cout << p.name << "  " << p.age << endl;
    cout << p2.name << "  " << p2.age << endl;
    cout << p3.name << "  " << p3.age << endl;

    cout << "          -----------------------------                  " << endl;

    // 显示
    Person p11;
    Person p22 = Person();
    Person p33 = Person("shibin", 19);
    Person p44 = Person(p33);

    // 隐式
    Person p111 = {"shibin", 19}; // 有参数构造
    Person p222 = p111;           // 拷贝构造
    Person p333 = 10;

    cout << p222.name << "  " << p222.age << endl;

    return 0;
}