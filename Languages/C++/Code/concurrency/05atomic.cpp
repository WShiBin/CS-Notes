#include <atomic>
#include <iostream>
#include <thread>

using namespace std;

//原子数据类型
atomic<long> total = {0}; //需要头文件 #include <atomic>

//点击函数
void func()
{
    for (int i = 0; i < 1000000; ++i)
    {
        total += 1;
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