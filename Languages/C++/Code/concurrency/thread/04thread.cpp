#include <stdio.h>
#include <stdlib.h>

#include <chrono>   // std::chrono::seconds
#include <iostream> // std::cout
#include <thread>   // std::thread, std::this_thread::sleep_for

using namespace std;

void thread_task(int n)
{
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "hello thread " << std::this_thread::get_id() << " paused " << n << " seconds" << std::endl;
}

int main(int argc, char *argv[])
{
    thread t(thread_task, 1);
    thread t2 = move(t);

    // move 之后, t 是not joinable, 否则terminating
    t.join();
    if (t.joinable())
    {
        t.join();
    }
    if (t2.joinable())
    {
        t2.join();
        cout << "joinable" << endl;
    }
    else
    {
        cout << "not joinable" << endl;
    }

    return 0;
}