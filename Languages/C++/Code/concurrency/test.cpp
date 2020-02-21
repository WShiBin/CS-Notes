#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char* argv[]) {
    std::thread t([]() {
        while (true) {
            cout << "from sub thread" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    std::this_thread::sleep_for(std::chrono::seconds(4));
    // detach 主线程退出, 子线程也会退出
    t.detach();
    cout << "main" << endl;
    return 0;
}