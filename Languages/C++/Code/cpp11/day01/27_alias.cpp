#include <iostream>
using namespace std;
#include <type_traits> //is_same<>所需头文件


//通过typedef给一个类型起别名，不能新建类型
typedef int int32;
using my_int=int;   //C++11方式

int main()
{
    //is_same判断2个类型是否一致，如果是返回真，否则返回假
    cout << is_same<int32, my_int>::value << endl;

    return 0;
}
