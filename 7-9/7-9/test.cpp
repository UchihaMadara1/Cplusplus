#define _CRT_SECURE_NO_WARNINGS



#include<iostream>

using namespace std;

template<typename Type>
void Print_Hello(Type a)
{
	cout << a << endl;
}
int main()
{
	Print_Hello(5);
	return 0;
}
