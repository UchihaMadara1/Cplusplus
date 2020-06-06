#define _CRT_SECURE_NO_WARNINGS

//链接：https ://www.nowcoder.com/questionTerminal/610e6c0387a0401fb96675f58cda8559
//来源：牛客网

//#include <iostream>
//(720)#include <math.h>
//using namespace std;
//
//int main(int argc, const char * argv[]) {
//	int n = 0;
//	//fTable[n]记录n个人都拿错（全不获奖）的情况种数，allTable[n]记录所有可能的组合情况n的阶乘
//	long long fTable[21] = { 0, 0, 1 }, allTable[21] = { 0, 1, 2 };
//	for (int i = 3; i < 21; ++i) {
//		//递推计算i个人全部拿错
//		fTable[i] = (i - 1) * (fTable[i - 1] + fTable[i - 2]);
//		//递推计算i的阶乘
//		allTable[i] = i * allTable[i - 1];
//	}
//	//scanf返回值为正确输入数据的变量个数，当一个变量都没有成功获取数据时，此时返回-1
//	while (scanf("%d", &n) != -1) {
//		//注意%属于控制字符，两个连续的%%才表示真正的%字符
//		printf("%4.2lf%%\n", 100 * double(fTable[n]) / allTable[n]);
//	}
//	return 0;
//}

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{
	string lst, nam;
	while (getline(cin, lst))
	{
		getline(cin, nam);
		vector<string> vs;
		for (size_t i = 0; i < lst.size(); ++i)
		{
			if (lst[i] == '\"')//有引号
			{
				vs.push_back(lst.substr(i + 1, lst.find('\"', i + 1) - i - 1));
				i = lst.find('\"', i + 1) + 1;
			}
			else//無引号
			{
				if (lst.find(',', i) == lst.npos)
				{
					vs.push_back(lst.substr(i, lst.size() - i));
					i = lst.size();
				}
				else
				{
					vs.push_back(lst.substr(i, lst.find(',', i) - i));
					i = lst.find(',', i);
				}
			}
		}
		cout << ((find(vs.begin(), vs.end(), nam) != vs.end()) ? "Ignore" : "Important!") << endl;
		//cout<<((find(v.begin(),v.end(),name)!=v.end())?"Ignore":"Important!")<<endl;
	}
	return 0;
}
