#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx2;
std::condition_variable cv2;

int cargo = 0;
static bool shipment_available()
{
    return cargo != 0;
}

// static void consume(int n)
static void consume()
{
    int n = 10;
    for (int i = 0; i < n; ++i)
    {
        std::unique_lock<std::mutex> lck(mtx2);
        cv2.wait(lck, shipment_available);
        // consume:
        std::cout << cargo << '\n';
        cargo = 0;
        std::cout << "****: " << cargo << std::endl;
    }
}

int main()
{
    std::thread consumer_thread(consume);

    // produce 10 items when needed:
    for (int i = 0; i < 10; ++i)
    {
        while (shipment_available())
            std::this_thread::yield();
        std::unique_lock<std::mutex> lck(mtx2);
        cargo = i + 1;
        cv2.notify_one();
    }

    consumer_thread.join();

    return 0;
}
