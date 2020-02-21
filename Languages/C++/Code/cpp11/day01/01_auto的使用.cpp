#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

double foo()
{
	return 1.1;
}

struct Test
{
	int a;
};

void func(vector<int> &tmp)
{
	for (auto i = tmp.begin(); i != tmp.end(); ++i)
	{
		//……
	}
}

int main(void)
{
	int a = 1;

	auto b = 1; //b的类型就是int

	auto c = foo(); //c的类型就是double

	Test str = {0};
	auto d = str; //d的类型就是struct Test

	printf("\n");
	system("pause");
	return 0;
}
