
#define _CRT_SECURE_NO_WARNINGS

//#include<iostream>
//#include<vector>
//#include<string>
//
//using namespace std;
////����ַ����е�����
//int main()
//{
//	string str;
//	while (getline(cin, str))
//	{
//		vector<char> iv;
//		for (int i = 0; i < str.size(); ++i)
//		{
//			if (str[i] >= '0'&&str[i] <= '9')
//				iv.push_back(str[i]);
//		}
//		for (auto &e : iv)
//			cout << e;
//		cout << endl;
//	}
//	return 0;
//}

//�Լ���һЩ����������λ����ָ��
// BFS�ⷨ��������һ������queueװ��pair<int x,int y>��������(��Ӧ��������)
//֮����ʹ��queue������Ϊ���е��Ƚ��ȳ��������ö�Ӧ��
//�����������(BFS)�ĵ���
//������Ϊ�������BFSЧ�ʸ�Щ����DFS�����Ϊû��ʹ�õݹ鷴�����¸������ֵ��
//ʱ�临�ӶȽϵͣ�����Ŀ�Թ���С��������ʱ��û��̫����
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int a[10][10] = { 0 };//��¼����״̬��0����û���߹�
char str[10][10];//��¼�Թ�
int bfs(int x0, int y0)
{
	queue<pair<int, int> > q;//�洢��������Ķ���
	pair<int, int> p;
	int x, y;
	q.push(make_pair(x0, y0));
	while (1)
	{
		p = q.front();
		x = p.first;
		y = p.second;
		if (x == 9 && y == 8)//�ߵ��յ���˳�ѭ��
			return a[9][8];
		/*
		������4��if��䣬�ֱ��Ӧ���ӵ��ϡ��¡������ĸ����ڵĸ���
		���������ӷ�������(���겻Խ�磬ͬʱ����'#'������֮ǰû���߹�)
		�Ͱ���������С�������Ҫע����ǣ������Ƚ��ȳ��ͱ�֤������ڽ���
		�������Ǳ������Զ�ĸ����ȴ���Ҳ����˵ֻ�е����(����ھ������2)
		�����и��Ӷ�pop()�����У����Ϊ3�ĸ��Ӳű�Ϊ����Ԫ�ء�������һ���
		���ӹ�ȣ�ֱ���ߵ����ڡ�
		��Ȼ��Ҳ������һ��forѭ����������4��if��������д����ϸ��*/
		if ((x - 1) >= 0 && (x - 1) <= 9 && y >= 0 && y <= 9 && a[x - 1][y] == 0 && str[x - 1][y] != '#')
		{
			a[x - 1][y] = a[x][y] + 1;
			q.push(make_pair(x - 1, y));
		}
		if ((x + 1) >= 0 && (x + 1) <= 9 && y >= 0 && y <= 9 && a[x + 1][y] == 0 && str[x + 1][y] != '#')
		{
			a[x + 1][y] = a[x][y] + 1;
			q.push(make_pair(x + 1, y));
		}
		if (x >= 0 && x <= 9 && (y - 1) >= 0 && (y - 1) <= 9 && a[x][y - 1] == 0 && str[x][y - 1] != '#')
		{
			a[x][y - 1] = a[x][y] + 1;
			q.push(make_pair(x, y - 1));
		}
		if (x >= 0 && x <= 9 && (y + 1) >= 0 && (y + 1) <= 9 && a[x][y + 1] == 0 && str[x][y + 1] != '#')
		{
			a[x][y + 1] = a[x][y] + 1;
			q.push(make_pair(x, y + 1));
		}
		q.pop();//�ж�����������4�����Ӻ�ø���Ӧ�ó���
	}
}
int main()
{
	char c;
	while (~scanf("%c", &c))
	{
		str[0][0] = c;
		for (int i = 1; i<10; i++)
		{
			scanf("%c", &c);
			str[0][i] = c;
		}
		getchar();//�Ե�ĩβ�Ļ��з�
		for (int i = 1; i<10; i++)
		{
			for (int j = 0; j<10; j++)
			{
				scanf("%c", &c);
				str[i][j] = c;
			}
			getchar();//�Ե�ĩβ�Ļ��з�
		}
		printf("%d\n", bfs(0, 1));
		memset(a, 0, sizeof(a));//��ʼ��ȫ�ֱ���a����
	}
	return 0;
}
//���ӣ�https://www.nowcoder.com/questionTerminal/6276dbbda7094978b0e9ebb183ba37b9?f=discussion
//��Դ��ţ����
//
////������DFS�ⷨ��������Ϊû��BFSЧ�ʸ�
////DFS���������������һ�����ߵ��ڣ�Ȼ���ٻ�������ԭֵС�͸���ԭֵ
////���Ա����������ܸ���һ�㣬����DFSʹ���˵ݹ�
//#include<iostream>
//#include<string.h>
//using namespace std;
//int a[10][10] = { 0 };
//char str[10][10];
//int dir[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
//void dfs(int x, int y)
//{
//	for (int i = 0; i<4; i++)
//	{
//		int m = x + dir[i][0];
//		int n = y + dir[i][1];
//		if (m >= 0 && m <= 9 && n >= 0 && n <= 9 && str[m][n] != '#')
//		{
//			if ((a[m][n] == 0) || (a[x][y] + 1)<a[m][n])
//			{
//				a[m][n] = a[x][y] + 1;
//				dfs(m, n);
//			}
//		}
//	}
//
//}
//int main()
//{
//	//  freopen("input.txt","r",stdin);
//	char c;
//	while (~scanf("%c", &c))
//	{
//		str[0][0] = c;
//		for (int i = 1; i<10; i++)
//		{
//			scanf("%c", &c);
//			str[0][i] = c;
//		}
//		getchar();
//		for (int i = 1; i<10; i++)
//		{
//			for (int j = 0; j<10; j++)
//			{
//				scanf("%c", &c);
//				str[i][j] = c;
//			}
//			getchar();
//		}
//		dfs(0, 1);
//		printf("%d\n", a[9][8]);
//		memset(a, 0, sizeof(a));
//	}
//	return 0;
//}