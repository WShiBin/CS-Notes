## 函数指针

```cpp
#include <iostream>

using namespace std;

typedef void (*PFT)(char, int);

void bar(char ch, int i)
{
    cout << "bar " << ch << ' ' << i << endl;
    return;
}

int main(int argc, char *argv[])
{
    // 定义一个函数对象
    PFT pft;
    pft = bar; // 赋值

    // 调用
    pft('e', 91);
    return 0;
}
```

传递函数指针

```cpp
#include <iostream>
using namespace std;
ˇ
typedef void (*PFT)(char, int);

void bar(char ch, int i)
{
    cout << "bar " << ch << ' ' << i << endl;
    return;
}

void foo(char ch, int i, PFT pft)
{
    pft(ch, i);
    return;
}

int main(int argc, char *argv[])
{
    // 传函数指针
    foo('i', 10, bar);
    return 0;
}
```



## 函数对象Function Object

具有函数功能的对象, 能像使用函数一样使用对象, 重写operator()操作符,

```cpp
#include <iostream>

using namespace std;

class F
{
public:
    void operator()()
    {
        cout << "operator = " << endl;
    }
};

int main(int argc, char *argv[])
{
    F f;
    f();
    return 0;
}
```

传递函数对象

```cpp
#include <iostream>

using namespace std;

class Fun
{
public:
    int operator()(int a, int b)
    {
        return a + b;
    }
};

void invokeFun(int a, int b, Fun &fun)
{
    int ret = fun(a, b);
    cout << "ret = " << ret << endl;
}

int main(int argc, char *argv[])
{
    Fun fun;
    invokeFun(10, 20, fun);
    return 0;
}
```

