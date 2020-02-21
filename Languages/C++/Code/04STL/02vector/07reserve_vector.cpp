#include <iostream>
#include <vector>
using namespace std;

int main()
{

    vector<int> v;

    //预先开辟空间
    v.reserve(100000);

    int *pStart = NULL;
    int count = 0;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
        if (pStart != &v[0])
        {
            pStart = &v[0];
            count++;
        }
    }

    cout << "count:" << count << endl;

    system("pause");
    return EXIT_SUCCESS;
}