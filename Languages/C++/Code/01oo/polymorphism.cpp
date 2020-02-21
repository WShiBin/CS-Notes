#include <iostream>

using namespace std;

class Animal
{
public:
    virtual void say()
    {
        cout << "Animal say" << endl;
    }
};

class Dog : public Animal
{
public:
    void say()
    {
        cout << "Dog say" << endl;
    }
};
class Cat : public Animal
{
public:
    void say()
    {
        cout << "Cat say" << endl;
    }
};

void doSpeak(Animal &animal)
{
    animal.say();
}

// 多态
// 1.有继承关系
// 2.重写父类虚函数
// 3.父类对象指向子类
int main(int argc, char *argv[])
{
    Cat cat;
    doSpeak(cat);

    Dog dog;
    doSpeak(dog);
    return 0;
}