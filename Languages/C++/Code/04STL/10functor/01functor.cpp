#include <iostream>
#include <utmp.h>
#include <utmpx.h>

using namespace std;

// 类似普通函数一样调用
// 有自己的变量
// 函数对象作为参数传递
class MyAdd
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};

class MyPrint
{
public:
    int count;
    MyPrint() : count(0) {}
    void operator()(const string str)
    {
        cout << str << endl;
        count++;
    }
};

void doPrint(MyPrint &myPrint, string str)
{
    myPrint(str);
}

int main(int argc, char *argv[])
{
    MyAdd myAdd;
    cout << myAdd(1, 2) << endl;
    MyPrint myPrint;
    myPrint("hello");
    myPrint("hello");
    myPrint("hello");
    myPrint("hello");
    cout << "count = " << myPrint.count << endl;

    doPrint(myPrint, string("from doPrint"));
    return 0;
}