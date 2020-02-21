#include <iostream>
#include <list>

using namespace std;

int main(int argc, char *argv[])
{

    list<int> myList;
    for (int i = 0; i < 10; i++)
    {
        myList.push_back(i);
    }

    for (list<int>::const_iterator begin = myList.begin(); begin != myList.end(); ++begin)
    {
        cout << *begin << " ";
    }
    cout << endl;

    // for (auto &val : myList)
    // {
    //     cout << val << " ";
    // }
    // cout << endl;

    // list<int>::pointer node = myList.
    // list<int>::_Nodeptr node = myList._Myhead->_Next;

    // for (int i = 0; i < myList._Mysize * 2; i++)
    // {
    //     cout << "Node:" << node->_Myval << endl;
    //     node = node->_Next;
    //     if (node == myList._Myhead)
    //     {
    //         node = node->_Next;
    //     }
    // }

    return 0;
}