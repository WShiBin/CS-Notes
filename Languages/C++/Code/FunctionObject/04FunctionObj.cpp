#include <iostream>

using namespace std;

class Fun
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};

void invokeFun(int a, int b, Fun &fun)
{
    int ret = fun(a, b);
    cout << "ret = " << ret << endl;
}

int main(int argc, char *argv[])
{
    Fun fun;
    invokeFun(10, 20, fun);
    return 0;
}