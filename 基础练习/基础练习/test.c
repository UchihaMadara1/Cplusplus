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
	if (year <= 0 || month <= 0 || month > 12)//�ж������Ƿ�Ϸ�
		return -1;
	if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))//�ж���һ���Ƿ�Ϊ����
		flag = 1;
	if (month == 2 && flag == 1)
		return 29;
	return days[month];
}
int Reverse_n(int num)
{
	int result = 0;
	// ����������
	for (int i = num; i;)
	{
		// ȥ����λ�ϵ���
		i = i / 10 * 10;
		// ��result��һλ�������ϵ�ǰ��λ�ϵ�����num-i��
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
		printf("������һ����(����-1����)��������ʼ��֤:>");
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
	printf("��������Ҫ���ҵ���ݺ��·�(����-1����):>");
	while (scanf("%d %d", &year, &month))
	{
		if (year == -1 || month == -1)
			break;
		printf("%d���%d����%d��\n",year,month,Judge_Days(year,month));
		printf("��������Ҫ���ҵ���ݺ��·�:>");
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
							printf("һ����%d�׽���",i);
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
	printf("������һ����������-1����:>");
	while (scanf("%d", &n) && n != -1)
	{
		printf("�������ת�����Ϊ %d \n",Reverse_n(n));
		printf("������һ����������-1����:>");
	}
}
int main()
{
	int key = 0;
	for (;;)
	{
		printf("������Ҫ��֤����Ŀ��ţ�>");
		scanf("%d", &key);//����Ҫ��֤����Ŀ��ţ�1 2 3 4
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
			printf("��������Ŀ����Ŀ����ȷ���!\n");
			break;
		}
	}
	return 0;
}
