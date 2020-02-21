#include <chrono>   // std::chrono::milliseconds
#include <iostream> // std::cout
#include <mutex>    // std::timed_mutex
#include <thread>   // std::thread

std::timed_mutex mtx;

void fireworks()
{
    // waiting to get a lock: each thread prints "-" every 200ms:
    while (!mtx.try_lock_for(std::chrono::milliseconds(200)))
    {
        std::cout << "-";
    }
    // got a lock! - wait for 1s, then this thread prints "*"
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "*\n";
    mtx.unlock();
}
void fireworks2()
{
    if (mtx.try_lock_for(std::chrono::milliseconds(200)))
    {
        std::cout << "------" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        mtx.unlock();
    }
}

// try_lock
// try_lock_for 等多长时间,没拿到锁不等了,返回false
// try_lock_util 等到一个时间点,没拿到锁, 不等了,返回false
int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(fireworks2);

    for (auto &th : threads)
        th.join();

    return 0;
}