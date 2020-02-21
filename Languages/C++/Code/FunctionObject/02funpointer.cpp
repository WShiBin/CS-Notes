#include <iostream>

using namespace std;

typedef void (*PFT)(char, int);

void bar(char ch, int i)
{
    cout << "bar " << ch << ' ' << i << endl;
    return;
}

void foo(char ch, int i, PFT pft)
{
    pft(ch, i);
    return;
}

int main(int argc, char *argv[])
{
    // 传函数指针
    foo('i', 10, bar);
    return 0;
}