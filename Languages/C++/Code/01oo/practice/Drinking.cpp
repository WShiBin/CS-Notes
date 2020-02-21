#include <iostream>

using namespace std;

class AbstractDrinking
{
public:
    // AbstractDrinking() {}
    virtual void boil() = 0;
    virtual void brew() = 0;
    virtual void pourInCup() = 0;
    virtual void putInSomething() = 0;
    void make()
    {
        boil();
        brew();
        pourInCup();
        putInSomething();
    }
};

class Coffee : public AbstractDrinking
{
public:
    Coffee() {}
    virtual void boil()
    {
        cout << "Coffee boil" << endl;
    }
    virtual void brew()
    {
        cout << "Coffee brew" << endl;
    }
    virtual void pourInCup()
    {
        cout << "Coffee pourInCup" << endl;
    }
    virtual void putInSomething()
    {
        cout << "Coffee putInSomething" << endl;
    }
};

void doWork(AbstractDrinking *drinking)
{
    drinking->make();
}

int main(int argc, char *argv[])
{
    // AbstractDrinking *drinking = new Coffee();
    // drinking->make();

    doWork(new Coffee());

    return 0;
}