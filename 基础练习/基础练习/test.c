#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>


bool ISInt5_7_multiple(int n)
{
	if (n % 5 == 0 && n % 7 == 0&&n != 0)
		return true;
	return false;
}
int Judge_Days(int year,int month)
{
	int flag = 0;
	int days[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	if (year <= 0 || month <= 0 || month > 12)//判断输入是否合法
		return -1;
	if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))//判断这一年是否为闰年
		flag = 1;
	if (month == 2 && flag == 1)
		return 29;
	return days[month];
}
int Reverse_n(int num)
{
	int result = 0;
	// 将整数倒序
	for (int i = num; i;)
	{
		// 去掉个位上的数
		i = i / 10 * 10;
		// 将result进一位，并加上当前个位上的数（num-i）
		result = result * 10 + num - i;

		i = i / 10;
		num = num / 10;
	}
	return result;
}
///////
void Case_One()
{
	int n = 0;
	while (n != -1)
	{
		printf("请输入一个数(输入-1结束)，即将开始验证:>");
		scanf("%d", &n);
		if (ISInt5_7_multiple(n) == true)
		{
			printf("yes\n");
		}
		else
		{
			printf("no\n");
		}
	}
}
void Case_Two()
{
	int year, month;
	printf("请输入你要查找的年份和月份(输入-1结束):>");
	while (scanf("%d %d", &year, &month))
	{
		if (year == -1 || month == -1)
			break;
		printf("%d年的%d月有%d天\n",year,month,Judge_Days(year,month));
		printf("请输入你要查找的年份和月份:>");
	}
}
void Case_Three()
{
	int i;
	for (i = 1;; i++)
	{
		if (i % 2 == 1)
		{
			if (i % 3 == 2)
			{
				if (i % 5 == 4)
				{
					if (i % 6 == 5)
					{
						if (i % 7 == 0)
						{
							printf("一共有%d阶阶梯",i);
							break;
						}
					}
				}
			}
		}
	}
}
void Case_Four()
{
	int n = 0;
	printf("请输入一个数，输入-1结束:>");
	while (scanf("%d", &n) && n != -1)
	{
		printf("这个数逆转后的数为 %d \n",Reverse_n(n));
		printf("请输入一个数，输入-1结束:>");
	}
}
int main()
{
	int key = 0;
	for (;;)
	{
		printf("请输入要验证的题目序号：>");
		scanf("%d", &key);//输入要验证的题目序号：1 2 3 4
		switch (key)
		{
		case 1:
			Case_One();
			break;
		case 2:
			Case_Two();
			break;
		case 3:
			Case_Three();
			break;
		case 4:
			Case_Four();
			break;
		default:
			printf("请输入项目内题目的正确序号!\n");
			break;
		}
	}
	return 0;
}
