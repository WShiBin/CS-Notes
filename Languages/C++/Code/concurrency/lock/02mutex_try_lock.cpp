#include <iostream> // std::cout
#include <mutex>    // std::mutex
#include <thread>   // std::thread

volatile int counter(0); // non-atomic counter
std::mutex mtx;          // locks access to counter

void attempt_10k_increases()
{
    for (int i = 0; i < 10000; ++i)
    {
        // try_lock
        // 1.如果当前线程被其它线程占有, try_lock返回false, 绕过,并不会阻塞
        if (mtx.try_lock())
        { // only increase if currently not locked:
            ++counter;
            mtx.unlock();
        }
    }
}

// try_lock:尝试去解锁, 解不开, 不解了
int main(int argc, const char *argv[])
{
    std::thread threads[10];
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(attempt_10k_increases);

    for (auto &th : threads)
        th.join();
    std::cout << counter << " successful increases of the counter.\n";

    return 0;
}