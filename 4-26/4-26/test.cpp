#define _CRT_SECURE_NO_WARNINGS


//oj:ɾ���ַ����е��ظ��ַ����±꿿����ַ���
#include<iostream>
#include<string>
using namespace std;

int main()
{
	string str;
	while (cin >> str)
	{
		int i = 0;
		int j = str.size();
		while (i < j)
		{
			int flag = 0;
			int left = str.find(str[i]);
			int right = str.rfind(str[i]);
			if (left != right)
			{
				for (int k = right; k < j - 1;++k)
					swap(str[k], str[k + 1]);
				str[j - 1] = 0;
				flag = 1;
			}
			if (flag == 0)
			{
				i++;
			}
			else
			{
				j--;
			}

		}
		cout << str << endl;
	}
	return 0;
}