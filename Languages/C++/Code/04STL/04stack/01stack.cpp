#include <iostream>
#include <stack>

using namespace std;

int main(int argc, char *argv[])
{
    // stack<T> stkT;                      //stack采用模板类实现， stack对象的默认构造形式：
    // stack(const stack &stk);            //拷贝构造函数

    stack<int> stk;
    stack<int> stk2(stk);

    // stack &operator=(const stack &stk); //重载等号操作符
    stack<int> stk3 = stk2;

    // push(elem);                         //向栈顶添加元素
    // pop();                              //从栈顶移除第一个元素
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);

    stk.pop();

    // top();                              //返回栈顶元素
    cout << "top = " << stk.top() << endl;

    // empty();                            //判断堆栈是否为空
    cout << "is empty ? " << stk.empty() << endl;

    // size();                             //返回堆栈的大小
    cout << "size is " << stk.size() << endl;

    return 0;
}