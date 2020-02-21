#include <iostream>

using namespace std;

template <class NameType, class AgeType>
class Person
{
public:
    NameType name;
    AgeType age;
    Person(NameType name, AgeType age);
    // {
    //     this->name = name;
    //     this->age = age;
    // }
    // : name(name), age(age) {}
    void show();
    // {
    //     cout << name << " - " << age << endl;
    // }
};

// 加上域,类型
template <class T1, class T2>
Person<T1, T2>::Person(T1 name, T2 age)
{
    this->name = name;
    this->age = age;
}

template <class T1, class T2>
void Person<T1, T2>::show()
{
    cout << name << " - " << age << endl;
}

/**
 * @brief 模版内的函数, 在外部实现
 */
int main(int argc, char *argv[])
{
    Person<string, int> p("shibin", 18);
    p.show();

    return 0;
}