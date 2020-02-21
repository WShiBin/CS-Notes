#include <chrono>             // std::chrono
#include <condition_variable> // std::condition_variable
#include <iostream>           // std::cout
#include <mutex>              // std::mutex, std::unique_lock
#include <thread>             // std::thread

std::mutex mtx;             // 全局互斥锁.
std::condition_variable cv; // 全局条件变量.
bool ready = false;         // 全局标志位.

void do_print_id(int id)
{
    std::unique_lock<std::mutex> lck(mtx); // 每个线程自己的lck
    while (!ready)
        cv.wait(lck); // 线程全部阻塞在这里

    std::cout << "thread id " << id << std::endl;
}

void go()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ready = true;
    cv.notify_all(); // 唤醒cv.wait的线程
    // cv.notify_one(); // 随机唤醒一个cv.wait()的线程
}

int main()
{
    std::thread threads[10];
    // spawn 10 threads:
    for (int i = 0; i < 10; ++i)
        threads[i] = std::thread(do_print_id, i);

    std::cout << "10 threads ready to race...\n";
    go(); // go!

    for (auto &th : threads)
        th.join();

    return 0;
}