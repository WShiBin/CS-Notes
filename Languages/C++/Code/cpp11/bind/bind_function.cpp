#include <functional>
#include <iostream>

using namespace std;

class Test
{
public:
    string msg;
    void func(string str)
    {
        cout << "str = " << str << endl;
    }
};
int main(int argc, char *argv[])
{
    Test t;
    function<void(string)> f = bind(&Test::func, &t, placeholders::_1);
    f("hello ");

    function<string &()> f2 = bind(&Test::msg, &t);
    f2() = "hehe";
    cout << "msg = " << t.msg << endl;

    // struct select1st s;

    return 0;
}