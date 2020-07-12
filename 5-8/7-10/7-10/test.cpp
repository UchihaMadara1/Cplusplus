#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

#pragma pack(4)

struct abb
{
	int a;
	int ai;
	char x;
	char y;
	char z;
	struct bbc
	{
		char b;
		double c;
		char d;
		int e;
	}stul;
}stu;
int main()
{
	cout << sizeof(stu) << endl;
	cout << sizeof(stu.stul) << endl;
	return 0;
}
