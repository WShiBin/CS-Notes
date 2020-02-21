#include <vector>
#include <algorithm> //std::for_each
#include <iostream>
using namespace std;

vector<int> nums;
vector<int> largeNums;

int main()
{
    for(int i = 0; i < 10; ++i)
    {
        nums.push_back(i+1);
    }
    int tmp = 5;

    for_each(nums.begin(), nums.end(),
        [&](int &n)
        {
            if(n > tmp)
            {
                largeNums.push_back(n);
            }
        }
    );


    for_each(largeNums.begin(), largeNums.end(),
        [](int &n)
        {
            cout << n << ", ";
        }
    );
    cout << endl;


    return 0;
}

int tmp = 5;

void func(int &n)
{
    if(n > tmp)
    {
        largeNums.push_back(n);
    }
}

void print(int &n)
{
    cout << n << ", ";
}

int main02()
{
    for(int i = 0; i < 10; ++i)
    {
        nums.push_back(i+1);
    }

    for_each(nums.begin(), nums.end(), func);
    /*
     for(auto itr = nums.begin(); itr != nums.end(); ++itr)
     {
        func(*itr);
     }
    */



    for_each(largeNums.begin(), largeNums.end(), print);
    cout << endl;
    /*
    for(auto itr = largeNums.begin(); itr != largeNums.end(); ++itr)
    {
        print(*itr);
    }
    */


    return 0;
}


int main01()
{
    for(int i = 0; i < 10; ++i)
    {
        nums.push_back(i+1);
    }
    int tmp = 5;

    //1¡¢´«Í³²Ù×÷
    for(auto itr = nums.begin(); itr != nums.end(); ++itr)
    {
        if(*itr > tmp)
        {
            largeNums.push_back(*itr);
        }
    }

    for(auto itr = largeNums.begin(); itr != largeNums.end(); ++itr)
    {
        cout << *itr << ", ";
    }
    cout << endl;



    return 0;
}
