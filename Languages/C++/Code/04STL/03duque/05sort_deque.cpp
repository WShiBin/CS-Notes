#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{

    deque<int> d;
    d.push_back(20);
    d.push_back(40);
    d.push_back(10);
    d.push_back(30);

    sort(d.begin(), d.end());

    for (auto &val : d)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}