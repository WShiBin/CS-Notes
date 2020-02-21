#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void)
{
	int a = 1024;
	char b = a; //ok, 数据丢失, 类型收窄
	printf("b = %d\n", b);

	printf("\n");
	system("pause");
	return 0;
}
