#include <iostream>

using namespace std;

// int add(int a, int b)
// {
//     return a + b;
// }

template <typename T>
int addWithTemplate(T a, T b)
{
    return a + b;
}

int main(int argc, char *argv[])
{
    int a = 100;
    int b = 10;
    char c = 'a';

    // cout << add(b, c) << endl;
    // cout << addWithTemplate(a, c) << endl;   // (int, char) err
    cout << addWithTemplate(a, b) << endl;      // (int, int) ok
    cout << addWithTemplate<int>(a, c) << endl; // (int, char) ok

    return 0;
}