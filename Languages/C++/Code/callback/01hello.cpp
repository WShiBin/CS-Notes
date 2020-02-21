#include <iostream>

using namespace std;

class CallbackInterface
{
public:
    // The prefix "cbi" is to prevent naming clashes.
    virtual int cbiCallbackFunction(int) = 0;
};

class Callee : public CallbackInterface
{
public:
    // The callback function that Caller will call.
    int cbiCallbackFunction(int i)
    {
        printf("  Callee::cbiCallbackFunction() inside callback\n");
        return 2 * i;
    }
};

class Caller
{
public:
    // Clients can connect their callback with this
    void connectCallback(CallbackInterface *cb)
    {
        m_cb = cb;
    }

    // Test the callback to make sure it works.
    void test()
    {
        printf("Caller::test() calling callback...\n");
        int i = m_cb->cbiCallbackFunction(10);

        printf("Result (20): %d\n", i);
    }

private:
    // The callback provided by the client via connectCallback().
    CallbackInterface *m_cb;
};

int main(int argc, char *argv[])
{

    Caller caller;
    Callee callee;

    // Connect the callback
    caller.connectCallback(&callee);

    // Test the callback
    caller.test();
    return 0;
}