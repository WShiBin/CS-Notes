#include <chrono>   // std::chrono::seconds
#include <iostream> // std::cout
#include <thread>   // std::thread, std::this_thread::sleep_for

void pause_thread(int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}

int main()
{
    std::cout << "Spawning and detaching 3 threads...\n";
    std::thread(pause_thread, 1).detach();
    std::thread(pause_thread, 2).detach();
    std::thread(pause_thread, 3).detach();

    // 默认线程不join,就会terminating, 这时候detach,就和主线程分离,
    // 如果主线程执行完了, 这个线程也会结束
    std::thread t(pause_thread, 4);
    t.detach();

    std::cout << "Done spawning threads.\n";

    std::cout << "(the main thread will now pause for 5 seconds)\n";
    // give the detached threads time to finish (but not guaranteed!):
    pause_thread(5);
    return 0;
}