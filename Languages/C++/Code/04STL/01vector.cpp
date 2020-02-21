#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main()
{

    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
        cout << v.capacity() << endl;
    }

    cout << " ------------- " << endl;
    int *start = &v[0];
    int *end = &v[v.size() - 1];

    for (; start <= end; start++)
    {
        cout << *start << endl;
    }

    return EXIT_SUCCESS;
}