#define _CRT_SECURE_NO_WARNINGS

/*
��ĿID��797 --���ݿ����ӳ�
���ӣ�https://www.nowcoder.com/questionTerminal/05f97d9b29944c018578d98d7f0ce56e
����˼·:
ʹ��һ��set���������ĳ����¼��connect���ͼӵ�set��ȥ�������disconnect��
�Ͱ�set�ж�Ӧ��ֵɾ�������ڼӽ�ȥ�Ĺ����У������ж�setԪ�ص�������������
����������������ɡ�
*/
//#include<iostream>
//#include<set>
//#include<string>
//#include<algorithm>
//#include<fstream>
//
//using namespace std;
//
//int main()
//{
//	int n;
//	while (cin >> n)
//	{
//		set<string> pool;
//		string id, con;
//		int Maxsize = 0;
//		for (int i = 0; i < n; ++i)
//		{
//			cin >> id >> con;
//			if (con == "connect")
//				pool.insert(id);
//			else if (con == "disconnect")
//				pool.erase(id);
//			int size = pool.size();
//			Maxsize = max(size, Maxsize);
//		}
//		cout << Maxsize << endl;
//	}
//	return 0;
//}

/*
	���ӣ�https://www.nowcoder.com/questionTerminal/433c0c6a1e604a4795291d9cd7a60c7a
��Դ��ţ����

�����У�ÿ��Ҫ����һ̨�»�����ʱ�򣬾���ζ����һ��Ŀ¼��Ҫ����������Ҫ����Ŀ¼��/usr/local/bin��������Ҫ�˴δ�����/usr������/usr/local���Լ���/usr/local/bin�������ڣ�Linux��mkdir�ṩ��ǿ��ġ�-p��ѡ�ֻҪһ�����mkdir -p /usr/local/bin�������Զ�������Ҫ���ϼ�Ŀ¼��
���ڸ���һЩ��Ҫ�������ļ���Ŀ¼�������æ������Ӧ�ġ�mkdir -p�����

*/
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>

using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		vector<string> list(n);
		vector<bool> flag(n, true);
		for (int i = 0; i < n; ++i)
			cin >> list[i];
		sort(list.begin(), list.end());
		for (int i = 0; i < list.size() - 1; ++i)
		{
			if (list[i] == list[i + 1])
				flag[i] = false;
			else if (list[i].size() < list[i + 1].size() && \
				list[i] == list[i + 1].substr(0, list[i].size()) && \
				list[i + 1][list[i].size()] == '/')
				flag[i] = false;
		}
		for (int i = 0; i < list.size(); ++i)
		{
			if (flag[i])
				cout << "mkdir -p " << list[i] << endl;
		}
		cout << endl;
	}
	return 0;
}