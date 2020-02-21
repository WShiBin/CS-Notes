#include <chrono>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;

void doSomething()
{
    volatile double d = 0;
    for (int n = 0; n < 10000; ++n)
        for (int m = 0; m < 10000; ++m)
            d += d * n * m;
}

int main(int argc, char *argv[])
{

    clock_t start = std::clock();
    doSomething();
    clock_t end = std::clock();                             // typedef unsigned long clock_t
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl; // CLOCKS_PER_SEC 1000000

    cout << " --------------- " << endl;

    auto start2 = std::chrono::system_clock::now();
    doSomething();
    std::time_t end_time = std::chrono::system_clock::to_time_t(start2); // typedef long time_t
    cout << "end_time = " << end_time << endl;
    cout << "end_time = " << std::ctime(&end_time) << endl;

    cout << " --------------- " << endl;

    std::time_t result = std::time(nullptr);
    cout << "result = " << result << " seconds " << endl;
    std::cout << std::asctime(std::localtime(&result)) << result << " seconds since the Epoch\n";

    // 1567412997033
    // System.out.println(System.currentTimeMillis()); java milliseconds默认秒
    long long timestamp_for_nano = system_clock::now().time_since_epoch().count(); // c++默认nano
    long long timestamp_for_mill = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long long timestamp_for_minutes = duration_cast<minutes>(system_clock::now().time_since_epoch()).count();

    cout << "timestamp(nano) = " << timestamp_for_nano << endl;
    cout << "timestamp(milliseconds) = " << timestamp_for_mill << endl;
    cout << "timestamp(minutes) = " << timestamp_for_minutes << endl;

    cout << " ------------------- " << endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    cout << t1.time_since_epoch().count() << endl;
    // cout << "t1 = " << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t1).count() << endl;

    return 0;
}