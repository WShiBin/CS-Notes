#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main()
{
	//强类型枚举， enum后面加上class或struct修饰
	enum class Status { Ok, Error };
	enum struct Status2 { Ok, Error };

	//Status flag = Ok; //err, 必须枚举类型的作用域
	Status flag = Status::Ok; //ok

	//强类型枚举，可以指定成员变量的类型
	enum struct Status3: char { Ok, Error };
	cout << sizeof(Status3::Ok) << endl;

	enum struct Status4: long long { Ok, Error };
	cout << sizeof(Status4::Ok) << endl;

	system("pause");
	return 0;
}

int main01(void)
{
	enum Status {Ok, Error};
	// “Ok”: 重定义；以前的定义是“枚举数”	
	//enum Status2 { Ok, Error };

	Status flag = Ok;

	cout << sizeof(Ok) << endl; //4


	system("pause");
	return 0;
}
