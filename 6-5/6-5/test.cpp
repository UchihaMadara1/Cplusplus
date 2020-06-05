#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<string>

using namespace std;


int main()
{
	string str1, str2;
	while (cin >> str1 >> str2)
	{
		int pos = 0,ret = 0;
		while (str1.find(str2, pos) != string::npos)
		{
			ret++;
			pos += str2.size();
		}
		cout<<ret<<endl;
	}
	return 0;
}
//int main()
//{
//	string s, t;
//	while (getline(cin, s) && getline(cin, t))
//	{
//		int flag = 0, i = 0, j = 0;
//		while (i < s.size())
//		{
//			if (s[i] == t[j] && j < t.size())
//			{
//				i++;
//				j++;
//			}
//			else
//			{
//				i = i - j + 1;
//				j = 0;
//			}
//			if (j == t.size())
//			{
//				j = 0;
//				flag++;
//			}
//		}
//		cout << flag << endl;
//	}
//	return 0;
//}
//int Fac_people(int day)
//{
//	int a = 1,b = 1;
//	while (day > 2)
//	{
//		a = a + b;
//		b = a - b;
//		day--;
//	}
//	return a;
//}
//int main()
//{
//	int ret = Fac_people(5);
//	return 0;
//}
//int main()
//{
//	int from, to;
//	while (cin >> from >> to)
//	{
//		int sum = 0;
//		for (int i = from; i <= to; ++i)
//			sum += Fac_people(i);
//		cout << sum << endl;
//	}
//	return 0;
//}
//int Fac_people(int day)
//{
//	int a = 1, b = 1;
//	while (day > 2)
//	{
//		a = a + b;
//		b = a - b;
//		day--;
//	}
//	return a;
//}
//int main()
//{
//	int from, to;
//	while (cin >> from >> to)
//	{
//		unsigned long long sum = 0;
//		for (int i = from; i <= to; ++i)
//			sum += Fac_people(i);
//		cout << sum << endl;
//	}
//	return 0;
//}