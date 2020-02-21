#include <iostream>

using namespace std;

class Callee
{
public:
    Callee(int i) : m_i(i) {}

    // The callback function that Caller will call.
    int callbackFunction(int i)
    {
        printf("  Callee::callbackFunction() inside callback\n");
        return m_i * i;
    }

private:
    // To prove "this" is indeed valid within callbackFunction().
    int m_i;
};

typedef std::function<int(int)> CallbackFunction;

class Caller
{
public:
    // Clients can connect their callback with this.
    void connectCallback(CallbackFunction cb)
    {
        cb.callbackFunction(1);
        m_cb = cb;
    }

    // Test the callback to make sure it works.
    void test()
    {
        printf("Caller::test() calling callback...\n");
        int i = m_cb(10);

        printf("Result (50): %d\n", i);
    }

private:
    // The callback provided by the client via connectCallback().
    CallbackFunction m_cb;
};

int main(int argc, char *argv[])
{
    Caller caller;
    Callee callee(5);

    // Connect the callback.  Like with the C-style function pointer and
    // static function, we use a lambda to get back into the object.
    caller.connectCallback([&callee](int i) {
        return callee.callbackFunction(i);
    });

    caller.connectCallback([&callee](int i) {
        printf("  Callee::callbackFunction() inside callback\n");
        return 9;
    });

    // Test the callback
    caller.test();

    return 0;
}