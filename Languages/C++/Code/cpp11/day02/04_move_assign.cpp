#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
public:
    MyString(const char *tmp = "abc")
    {//普通构造函数
        len = strlen(tmp);  //长度
        str = new char[len+1]; //堆区申请空间
        strcpy(str, tmp); //拷贝内容

        cout << "普通构造函数 str = " << str << endl;
    }

    MyString(const MyString &tmp)
    {//拷贝构造函数
        len = tmp.len;
        str = new char[len + 1];
        strcpy(str, tmp.str);

        cout << "拷贝构造函数 tmp.str = " << tmp.str << endl;
    }

    //移动构造函数
    //参数是非const的右值引用
    MyString(MyString && t)
    {
        str = t.str; //拷贝地址，没有重新申请内存
        len = t.len;

        //原来指针置空
        t.str = NULL;
        cout << "移动构造函数" << endl;
    }

    MyString &operator= (const MyString &tmp)
    {//赋值运算符重载函数
        if(&tmp == this)
        {
            return *this;
        }

        //先释放原来的内存
        len = 0;
        delete []str;

        //重新申请内容
        len = tmp.len;
        str = new char[len + 1];
        strcpy(str, tmp.str);

         cout << "赋值运算符重载函数 tmp.str = " << tmp.str << endl;

        return *this;

    }

    //移动赋值函数
    //参数为非const的右值引用
    MyString &operator=(MyString &&tmp)
    {
        if(&tmp == this)
        {
            return *this;
        }

        //先释放原来的内存
        len = 0;
        delete []str;

        //无需重新申请堆区空间
        len = tmp.len;
        str = tmp.str; //地址赋值
        tmp.str = NULL;

        cout << "移动赋值函数\n";

        return *this;
    }

    ~MyString()
    {//析构函数
        cout << "析构函数: ";
        if(str != NULL)
        {
            cout << "已操作delete, str =  " << str;
            delete []str;
            str = NULL;
            len = 0;

        }
        cout << endl;
    }

private:
    char *str = NULL;
    int len = 0;
};

MyString func() //返回普通对象，不是引用
{
    MyString obj("mike");

    return obj;
}

int main()
{
    MyString tmp("abc"); //实例化一个对象
    tmp = func();

    return 0;
}
