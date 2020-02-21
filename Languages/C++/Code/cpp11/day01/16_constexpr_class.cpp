#include <iostream>
using namespace std;

class Date
{
public:
    //constexpr修饰构造函数，构造函数体必须为空
    constexpr Date(int y, int m, int d):year(y), month(m), day(d)
    {

    }

    constexpr int GetYear()
    {
        return year;
    }

    constexpr int GetMonth()
    {
        return year;
    }

    constexpr int GetDate()
    {
        return year;
    }

private:
    int year;
    int month;
    int day;
};

int main()
{
    constexpr Date obj(2017, 10, 10); //必须使用常量给构造函数传参
    cout << obj.GetYear() << endl;

    return 0;
}
