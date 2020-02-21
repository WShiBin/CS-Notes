#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

//全局的结果数据
long total = 0;
mutex g_lock;

//点击函数
void func()
{
    for (int i = 0; i < 1000000; ++i)
    {
        g_lock.lock(); //加锁
        total += 1;
        g_lock.unlock(); //解锁
    }
}

int main()
{
    clock_t start = clock(); // 计时开始

    //线程
    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();

    clock_t end = clock(); // 计时结束

    cout << "total = " << total << endl;
    cout << "time = " << end - start << " ms\n";

    return 0;
}