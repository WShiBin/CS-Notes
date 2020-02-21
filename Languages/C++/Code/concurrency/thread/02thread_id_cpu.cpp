#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

void fun()
{
    this_thread::sleep_for(chrono::seconds(3));
    cout << "fun thread id = " << this_thread::get_id() << endl;
}

int main(int argc, char *argv[])
{
    thread t(fun);
    cout << "t thread id = " << t.get_id() << endl;
    cout << "main thread id = " << this_thread::get_id() << endl;

    cout << "cpu count = " << thread::hardware_concurrency() << endl;

    t.join();

    return 0;
}