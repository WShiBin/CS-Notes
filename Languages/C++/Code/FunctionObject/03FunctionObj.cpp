#include <iostream>

using namespace std;

class F
{
public:
    void operator()()
    {
        cout << "operator = " << endl;
    }
};

int main(int argc, char *argv[])
{
    F f;
    f();
    return 0;
}