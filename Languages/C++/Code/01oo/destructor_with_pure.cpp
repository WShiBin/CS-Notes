#include <iostream>

using namespace std;

class Animal
{
public:
    Animal()
    {
        cout << "Animal construct" << endl;
    }
    virtual void speak() = 0;
    // 在父类的析构上加virtual keyword, 会去调用子类的析构函数
    // 父类析构函数必需要实现,如果自己是纯虚函数,那就要在外部实现
    virtual ~Animal() = 0;
    // {
    //     cout << "Animal Destructor" << endl;
    // }
};

// 外部实现
Animal::~Animal()
{
    cout << "Animal Destructor" << endl;
}

class Cat : public Animal
{
public:
    string *m_Name;
    Cat(string name)
    {
        cout << "Cat construct" << endl;
        m_Name = new string(name);
    }
    virtual void speak()
    {
        cout << *m_Name << " cat speak ~~~~~~~ " << endl;
    }
    virtual ~Cat()
    {
        cout << "Cat Destructor" << endl;
        // cout << " ~~~ Cat" << endl;
        if (m_Name != nullptr)
        {
            delete m_Name;
            m_Name = nullptr;
        }
    }
};

// void doSpeak(Animal *animal)
// {
//     animal->speak();
// }

void test()
{
    Animal *animal = new Cat("Tom");
    animal->speak();

    if (animal != NULL)
        delete animal;
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}