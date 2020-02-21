#include <cmath>
#include <functional>
#include <future>
#include <iostream>
#include <thread>
#include <random>

using namespace std;

int fun(int a, int b)
{
    // std::default_random_engine dre;
    return std::pow(a, b);
}
void task_lambda()
{
    std::packaged_task<int(int, int)> p([](int a, int b) {
        return std::pow(a, b);
    });
    std::future<int> f = p.get_future();
    p(3, 3);
    cout << f.get() << endl;
}

void task_bind()
{
    std::packaged_task<int()> p(std::bind(fun, 3, 3));
    std::future<int> f = p.get_future();
    p();
    f.wait();
    std::cout << f.get() << std::endl;
}

void task_fun()
{
    std::packaged_task<int(int, int)> p(fun);
    std::future<int> f = p.get_future();
    std::thread t(std::move(p), 3, 4);
    t.join();
    std::cout << f.get() << std::endl;
}

int main(int argc, char *argv[])
{
    // task_fun();
    // task_bind();
    task_lambda();


    int a{10};

    return 0;
}