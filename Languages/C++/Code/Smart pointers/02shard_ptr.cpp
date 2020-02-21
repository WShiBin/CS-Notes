#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    std::shared_ptr<int> p1(new int(5));
    std::shared_ptr<int> p2 = p1; // 都指向同一内存。

    cout << *p1 << endl;
    p1.reset(); // 因为p2还在，所以内存没有释放。
    cout << *p2 << endl;
    p2.reset(); // 释放内存，因为没有shared_ptr指向那块内存了。
    return 0;
}