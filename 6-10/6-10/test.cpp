#define _CRT_SECURE_NO_WARNINGS

/*
题目ID：797 --数据库连接池
链接：https://www.nowcoder.com/questionTerminal/05f97d9b29944c018578d98d7f0ce56e
解题思路:
使用一个set来做，如果某个记录是connect，就加到set中去，如果是disconnect，
就把set中对应的值删除掉。在加进去的过程中，不断判断set元素的最大个数，最终
返回这个最大个数即可。
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
	链接：https://www.nowcoder.com/questionTerminal/433c0c6a1e604a4795291d9cd7a60c7a
来源：牛客网

工作中，每当要部署一台新机器的时候，就意味着有一堆目录需要创建。例如要创建目录“/usr/local/bin”，就需要此次创建“/usr”、“/usr/local”以及“/usr/local/bin”。好在，Linux下mkdir提供了强大的“-p”选项，只要一条命令“mkdir -p /usr/local/bin”就能自动创建需要的上级目录。
现在给你一些需要创建的文件夹目录，请你帮忙生成相应的“mkdir -p”命令。

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