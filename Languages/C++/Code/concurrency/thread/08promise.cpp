#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <string>
#include <thread>
#include <vector>

void accumulate(std::vector<int>::iterator first, std::vector<int>::iterator last, std::promise<int> accumulate_promise)
{
    int sum = std::accumulate(first, last, 0);
    accumulate_promise.set_value(sum);
    // accumulate_promise.set_value_at_thread_exit(sum);
}

void do_work(std::promise<void> barrier)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    barrier.set_value();
}

void do_something(std::promise<std::string> barrier)
{
    barrier.set_value("from so domething");
}

int main()
{
    std::promise<std::string> p;
    std::future<std::string> f = p.get_future();

    std::thread t(do_something, std::move(p));
    f.wait();
    t.join();
    std::cout << f.get() << std::endl;

    return EXIT_SUCCESS;
}