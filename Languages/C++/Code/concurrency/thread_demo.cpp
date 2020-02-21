#include <chrono>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

// The function we want to execute on the new thread.
void task1(string msg, string msg3)
{
    cout << "task1 says: " << msg << " " + msg3 << endl;
}

int main()
{
    // Constructs the new thread and runs it. Does not block execution.
    std::thread t1(task1, "Hello", "world");

    // Do other things...
    this_thread::sleep_for(chrono::seconds(4));

    // Makes the main thread wait for the new thread to finish execution, therefore blocks its own execution.
    // 等待线程执行完
    t1.join();
}