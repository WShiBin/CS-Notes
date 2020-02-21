#include <iostream>
#include <set>
// #include <mutil

using namespace std;

int main(int argc, char *argv[])
{
    set<int> s;
    s.insert(10);
    pair<set<int>::iterator, bool> p = s.insert(10);
    if (p.second)
    {
        cout << "success " << endl;
    }
    else
    {
        cout << "failed " << endl;
    }

    multiset<int> ms;
    ms.insert(10);
    pair<multiset<int>::iterator, bool> p2;
    multiset<int>::iterator it = ms.insert(10);
    for (auto &val : ms)
    {
        cout << val << " ";
    }
    cout << endl;
    // if (p2.second)
    // {
    //     cout << "mutilset insert success " << endl;
    // }
    // else
    // {
    //     cout << "mutilset insert failed " << endl;
    // }
    return 0;
}