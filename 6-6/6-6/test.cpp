#define _CRT_SECURE_NO_WARNINGS

//���ӣ�https ://www.nowcoder.com/questionTerminal/610e6c0387a0401fb96675f58cda8559
//��Դ��ţ����

//#include <iostream>
//(720)#include <math.h>
//using namespace std;
//
//int main(int argc, const char * argv[]) {
//	int n = 0;
//	//fTable[n]��¼n���˶��ô�ȫ���񽱣������������allTable[n]��¼���п��ܵ�������n�Ľ׳�
//	long long fTable[21] = { 0, 0, 1 }, allTable[21] = { 0, 1, 2 };
//	for (int i = 3; i < 21; ++i) {
//		//���Ƽ���i����ȫ���ô�
//		fTable[i] = (i - 1) * (fTable[i - 1] + fTable[i - 2]);
//		//���Ƽ���i�Ľ׳�
//		allTable[i] = i * allTable[i - 1];
//	}
//	//scanf����ֵΪ��ȷ�������ݵı�����������һ��������û�гɹ���ȡ����ʱ����ʱ����-1
//	while (scanf("%d", &n) != -1) {
//		//ע��%���ڿ����ַ�������������%%�ű�ʾ������%�ַ�
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
			if (lst[i] == '\"')//������
			{
				vs.push_back(lst.substr(i + 1, lst.find('\"', i + 1) - i - 1));
				i = lst.find('\"', i + 1) + 1;
			}
			else//�o����
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
