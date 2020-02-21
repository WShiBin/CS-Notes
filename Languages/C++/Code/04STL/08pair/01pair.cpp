#include <iostream>
// #include <pair>

using namespace std;

int main(int argc, char *argv[])
{
    // const char *name = "shibin";
    pair<string, int> p("shibin", 19);
    cout << p.first << " - " << p.second << endl;

    pair<string, int> p2 = make_pair("shibin", 18);
    cout << p2.first << " - " << p2.second << endl;
    p2.second = 20;

    pair<string, int> p3 = p2;
    cout << p3.first << " - " << p3.second << endl;

    return 0;
}