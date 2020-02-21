#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
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

int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector<int> numbers{1, 2, 3, 4, 5, 6};
    std::promise<int> accumulate_promise;
    std::future<int> accumulate_future = accumulate_promise.get_future();
    // std::thread accumulate_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
    std::thread accumulate_thread(accumulate, numbers.begin(), numbers.end(), std::move(accumulate_promise));
    // accumulate_future.wait();
    std::cout << accumulate_future.get() << std::endl;
    accumulate_thread.join();

    // Demonstrate using promise<void> to signal state between threads.
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread new_work_thread(do_work, std::move(barrier));
    barrier_future.wait();
    new_work_thread.join();
    return EXIT_SUCCESS;
}