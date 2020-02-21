#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

//2、vs2013不支持，函数形参是auto变量, qt确实可以
void func(auto a)
{

}

//3、auto变量不能作为自定义类型的成员变量
struct  Test
{
	int a;
	auto b = 10;
};

int main(void)
{
	//1、定义变量时，必须初始化
	auto a;
	a = 10;

	auto b[3] = { 1, 2, 3 }; //4、不能是auto数组

	//5、模板实例化类型不能是auto类型
	vector<int> a;
	vector<auto> b = { 1 };


	system("pause");
	return 0;
}
