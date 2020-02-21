#include <iostream>
#include <thread>

using namespace std;

mutex mtx; //全局互斥锁对象，#include <mutex>

// 打印机
void printer(const char *str)
{
    mtx.lock(); //上锁
    while (*str != '\0')
    {
        std::cout << *str;
        str++;
        this_thread::sleep_for(chrono::seconds(1));
    }
    // cout << endl;

    mtx.unlock(); //解锁
}

// 线程一
void func1()
{
    const char *str = "hello";
    printer(str);
}

// 线程二
void func2()
{
    const char *str = "world";
    printer(str);
}

// 互斥
// std::mutex，最基本的 Mutex 类。
// std::recursive_mutex，递归 Mutex 类。
// std::time_mutex，定时 Mutex 类。
// std::recursive_timed_mutex，定时递归 Mutex 类。
int main(void)
{
    thread t1(func1);
    thread t2(func2);

    t1.join();
    t2.join();

    return 0;
}