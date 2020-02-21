#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;


void func01()
{
	throw 1;
}

//这个函数不能抛出任何异常
void func02() throw()
{

}

//这个函数不能抛出任何异常
//noexcept vs 2013不支持，换在qt下测试
void func03() noexcept
{

}

int main(void)
{

	system("pause");
	return 0;
}
