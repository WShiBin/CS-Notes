#include <chrono>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

void fun(std::promise<int> pp)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pp.set_value(1000);
}

int main(int argc, char *argv[])
{
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t(fun, std::move(p));
    f.wait();
    std::cout << f.get() << std::endl;
    t.join();

    return 0;
}