#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<vector>

using namespace std;
void Su_data_sub(int &b)
{
	int a = b;
	vector<int> iv;
	vector<int> ret;
	int i, j;
	for (i = 2; i <= a; ++i)
	{
		for (j = 2; j < i; ++j)
		{
			if (i % j == 0)
				break;
		}
		if (i == j)
			iv.push_back(i);
	}
	i = 0;
	while (a != 1)
	{
		if (i < iv.size()&&a % iv[i] == 0)
		{
			ret.push_back(iv[i]);
			a /= iv[i];
			continue;
		}
		else
		{
			i++;
		}
	}
	ret.push_back(0);
	i = 0;
	cout << b << " = ";
	while (ret[i] != 0)
	{
		cout << ret[i] ;
		if (ret[i + 1] != 0)
			cout << " * ";
		i++;
	}
}
int main()
{
	int a;
	while (cin >> a)
	{
		Su_data_sub(a);
	}
	return 0;
}