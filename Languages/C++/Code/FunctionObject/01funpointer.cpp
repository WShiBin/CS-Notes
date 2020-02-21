#include <iostream>

using namespace std;

typedef void (*PFT)(char, int);

void bar(char ch, int i)
{
    cout << "bar " << ch << ' ' << i << endl;
    return;
}

int main(int argc, char *argv[])
{
    // 定义一个函数对象
    PFT pft;
    pft = bar; // 赋值

    // 调用
    pft('e', 91);
    return 0;
}