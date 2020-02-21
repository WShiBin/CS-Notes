#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    auto begin = v.begin();
    // vector<int>::iterator it_begin = v.begin();
    vector<int>::iterator it_end = v.end();
    // while (begin != it_end)
    // {
    //     cout << *begin << endl;
    //     begin++;
    // }

    // for (auto begin = v.begin(); begin != v.end(); ++begin)
    // {
    //     cout << *begin << endl;
    // }

    for_each(v.begin(), v.end(), [](int item) {
        cout << item << endl;
    });

    // for (auto &val : v)
    // {
    //     cout << val << endl;
    // }

    return 0;
}