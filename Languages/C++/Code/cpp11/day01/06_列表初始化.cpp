#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct Test
{
	int a;
	int b;
	char name[50];
};

int main(void)
{
	struct Test tmp = {1, 2, "mike"}; //列表初始化

	int a = 1;
	int b = { 1 }; //ok, 列表初始化
	int c{ 2 }; //ok

	int arr[] = { 1, 2, 3 };
	int arr2[]{ 1, 2, 3 };


	system("pause");
	return 0;
}
