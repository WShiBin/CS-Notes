#include <iostream>
#include <memory> //智能指针头文件
using namespace std;

class Test
{
public:
    ~Test()
    {
        cout << "析构\n";
    }
};

int main04()
{
    unique_ptr<int> up1(new int(11));

    //释放控制权，不释放堆区内存
    int * p = up1.release();
    cout << *p << endl;
    //cout << *up1 << endl; //err

    delete p;


    return 0;
}

int main03()
{
    unique_ptr<int> up1(new int(11));

    //up1.reset(); //如果是无参，作用是显式释放堆区内容

    //如果有参数，先释放原来堆区内容，重新给up1绑定一个新的堆区内容
    up1.reset(new int(22));
    cout << *up1 << endl;

    return 0;
}

int main02()
{
    unique_ptr<int> up1(new int(11)); //创建智能指针对象, up1是唯一使用者
    //unique_ptr<int> up2 = up1; //禁用拷贝构造， err

    //把up1的使用权，转义给up2, up1不能再操作堆区空间
    unique_ptr<int> up2 = std::move(up1);
    cout << "*up2 = " << *up2 << endl;
    //cout << "*up1 = " << *up1 << endl; //err

    return 0;
}

int main()
{
    unique_ptr<int> up1(new int(11)); //创建智能指针对象
    cout << "*up1 = " << *up1 << endl; //重载了operator *()

    {
        unique_ptr<Test> up2(new Test); //无需释放，自动释放

        //人为指定释放堆区空间
        up2 = nullptr;  //1
        up2 = NULL;     //2
        up2.reset();
        up2.reset();

        cout << "111111111\n";


    }
    cout << "-----------------\n";

    return 0;
}

