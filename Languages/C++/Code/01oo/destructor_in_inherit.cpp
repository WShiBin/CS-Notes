#include <iostream>

using namespace std;

class Animal
{
public:
    Animal()
    {
        cout << "Animal construct" << endl;
    }
    // 纯虚函数,不能实例化
    virtual void speak() = 0;
    // 在父类的析构上加virtual keyword, 会去调用子类的析构函数
    virtual ~Animal()
    {
        cout << "Animal Destructor" << endl;
    }
};

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
    // Animal a(); // err
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