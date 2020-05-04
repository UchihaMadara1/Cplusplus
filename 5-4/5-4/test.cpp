#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
using namespace std;

//排列问题
//template<class Type>
//void Perm(Type list[],int k,int m)
//{
//	//产生list[k:m]的所有排列
//	if (k == m)
//	{
//		//单元素序列
//		for (int i = 0; i <= m; ++i)
//			cout << list[i];
//		cout << endl;
//	}
//	else
//	{
//		//多元素序列，递归产生排列
//		for (int i = k; i <= m; ++i)
//		{
//			Swap(list[k],list[i]);
//			Perm(list,k + 1,m);
//			Swap(list[k],list[i]);
//		}
//	}
//}
//template<class Type>
//inline void Swap(Type &a, Type &b)
//{
//	Type tmp = a;
//	a = b;
//	b = tmp;
//}
//int main()
//{
//	return 0;
//}


//整数划分问题
int q(int n,int m)
{
	if ((n < 1) || (m < 1))
		return 0;
	if ((n == 1) || (m == 1))
		return 1;
	if (n < m)
		return q(n,n);
	if (n == m)
		return q(n, m - 1) + 1;
	return q(n, m - 1) + q(n - m,m);
}