#include <iostream>
#include <set>

using namespace std;

class MyCompare
{
public:
    // 方法后面加const, error: the specified comparator type does not provide a const call operator
    bool operator()(const int &a, const int &b) const
    {
        return a > b;
    }
};

int main(int argc, char *argv[])
{
    set<int, MyCompare> s;
    s.insert(10);
    s.insert(20);
    s.insert(30);
    s.insert(40);
    s.insert(50);

    for (auto begin = s.begin(); begin != s.end(); ++begin)
    {
        cout << *begin << " ";
    }
    cout << endl;

    return 0;
}