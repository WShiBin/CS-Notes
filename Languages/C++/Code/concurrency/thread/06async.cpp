#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int simplefunc(std::string a)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return a.size();
}

int main()
{
    std::future<int> f = std::async(simplefunc, "hello world");
    int ret = f.get();
    std::cout << "result = " << ret << std::endl;

    std::cout << "main" << std::endl;
    return EXIT_SUCCESS;
}