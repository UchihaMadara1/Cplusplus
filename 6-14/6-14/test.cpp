
#define _CRT_SECURE_NO_WARNINGS

//#include<iostream>
//#include<vector>
//#include<string>
//
//using namespace std;
////输出字符串中的数字
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

//自己的一些看法，望各位批评指正
// BFS解法，利用了一个队列queue装载pair<int x,int y>类型数据(对应格子坐标)
//之所以使用queue，是因为队列的先进先出特性正好对应了
//广度优先搜索(BFS)的迭代
//个人认为这道题用BFS效率高些，与DFS相比因为没有使用递归反复更新格子里的值，
//时间复杂度较低，但题目迷宫较小所以运行时间没有太大差别。
#include<iostream>
#include<queue>
#include<string.h>
using namespace std;
int a[10][10] = { 0 };//记录格子状态，0代表没有走过
char str[10][10];//记录迷宫
int bfs(int x0, int y0)
{
	queue<pair<int, int> > q;//存储格子坐标的队列
	pair<int, int> p;
	int x, y;
	q.push(make_pair(x0, y0));
	while (1)
	{
		p = q.front();
		x = p.first;
		y = p.second;
		if (x == 9 && y == 8)//走到终点就退出循环
			return a[9][8];
		/*
		下面是4个if语句，分别对应格子的上、下、左、右四个相邻的格子
		如果这个格子符合条件(坐标不越界，同时不是'#'，并且之前没有走过)
		就把它放入队列。这里需要注意的是，队列先进先出就保证了离出口近的
		格子总是比离出口远的格子先处理，也就是说只有当广度(离出口距离比如2)
		的所有格子都pop()出队列，广度为3的格子才变为队首元素。就这样一点点
		增加广度，直到走到出口。
		当然你也可以用一个for循环替代这里的4个if，但我想写的详细点*/
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
		q.pop();//判断完上下左右4个格子后该格子应该出队
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
		getchar();//吃掉末尾的换行符
		for (int i = 1; i<10; i++)
		{
			for (int j = 0; j<10; j++)
			{
				scanf("%c", &c);
				str[i][j] = c;
			}
			getchar();//吃掉末尾的换行符
		}
		printf("%d\n", bfs(0, 1));
		memset(a, 0, sizeof(a));//初始化全局变量a数组
	}
	return 0;
}
//链接：https://www.nowcoder.com/questionTerminal/6276dbbda7094978b0e9ebb183ba37b9?f=discussion
//来源：牛客网
//
////下面是DFS解法，个人认为没有BFS效率高
////DFS深度优先搜索就是一条道走到黑，然后再回来，比原值小就更新原值
////所以遍历次数可能更多一点，另外DFS使用了递归
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