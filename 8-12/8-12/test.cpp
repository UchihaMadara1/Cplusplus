#define _CRT_SECURE_NO_WARNINGS


#include<iostream>

using namespace std;

int fun(unsigned int x)
{
	int n = 0;
	while (x + 1)
	{
		n++;
		x = x | (x + 1);
	}
	return n;
}

int main()
{
	cout << fun(2014) << endl;;
	return 0;
}