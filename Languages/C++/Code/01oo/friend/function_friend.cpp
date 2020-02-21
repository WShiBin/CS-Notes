#include <iostream>

using namespace std;
class GoodGay
{
public:
    Building *building;
    GoodGay();
    void visit();
    void visit2();
};

class Building
{
    // 友元 GoodGay::visit函数是我这个类的朋友,
    // 在GoodGay::visit方法中,Building的对象可以访问自己的私有成员
    friend void GoodGay::visit();

public:
    string hehe;

private:
    string xixi;
};

void GoodGay::visit()
{
    building->xixi;
    building->hehe;
}
void GoodGay::visit2()
{
    // building->xixi; // can not access
    building->hehe;
}
int main(int argc, char *argv[])
{

    return 0;
}