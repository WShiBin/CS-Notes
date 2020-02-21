#include <iostream>
#include <thread>

using namespace std;

void fun()
{
    cout << "fun" << endl;
}
void fun2(int num)
{
    cout << "num =  " << num << endl;
}

class Printer
{
public:
    void operator()(int num)
    {
        cout << "num = " << num << endl;
    }
};

int main(int argc, char *argv[])
{
    // hello
    thread t1(fun);
    t1.join();

    // 线程传参
    thread t2(fun2, 10);
    t2.join();

    // thread 与 lambda
    thread t3([]() {
        cout << "thread t3" << endl;
    });
    if (t3.joinable())
        t3.join();

    // thread 与 仿函数
    thread t4(Printer(), 10);
    t4.join();

    return 0;
}