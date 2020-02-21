#include <chrono> // std::chrono::seconds
#include <iostream>
#include <thread> // std::thread, std::this_thread::sleep_for

using namespace std;

class Person
{
public:
    int *m_age;
    Person(int age)
    {
        // this->age = new int(age);
        m_age = new int(age);
    }

    ~Person()
    {
        if (m_age != nullptr)
        {
            delete m_age;
            m_age = nullptr;
        }
    }

    // 拷贝构造
    Person &operator=(Person &p)
    {
        if (m_age != nullptr)
        {
            delete m_age;
            m_age = nullptr;
        }
        this->m_age = new int(*p.m_age);
        return *this;
    }
};

// ostream &operator<<(ostream &cout, Person &p)
// {
//     cout << p.age << endl;
//     return cout;
// }

int main(int argc, char *argv[])
{
    Person p(18);
    Person p2(20);
    p2 = p;

    cout << *p.m_age << endl;

    this_thread::sleep_for(chrono::seconds(10));
    return 0;
}