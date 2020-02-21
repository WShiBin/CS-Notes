#include <functional>
#include <iostream>
#include <vector>

// #use namespace std;
class observer
{
public:
    virtual void notify() = 0;
};

class observer_concrete : public observer
{
public:
    virtual void notify() override
    {
        // std::cout << std::count << "hello " << std::end;
        std::cout << "hello" << std::endl;
    }
};

class subject
{
public:
    void register_observer(observer &o)
    {
        observers.push_back(o);
    }
    void notify_observers()
    {
        for (observer &o : observers)
        {
            o.notify();
        }
    }

private:
    std::vector<std::reference_wrapper<observer>> observers;
};

int main(int argc, char *argv[])
{
    subject s;

    observer_concrete o1, o2;
    s.register_observer(o1);
    s.register_observer(o2);

    s.notify_observers();
}