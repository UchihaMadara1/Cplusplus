#define _CRT_SECURE_NO_WARNINGS
/*
��Ŀ���⣺������һ���а��ա�a1/b1 a2/b2���ĸ�ʽ��������������ʽ����������
���з��Ӻͷ�ĸȫ�����ͷ�Χ�ڵ�����������ֻ���ܳ����ڷ���ǰ����ĸ��Ϊ0��
�ֱ���4���а��ա�������1 ����� ������2 = ������ĸ�ʽ˳�����2����������
�͡�������̡�ע�������ÿ�������������Ǹ��������������ʽ��k a/b��������
k���������֣�a/b�����������֣���Ϊ��������������ţ���������ĸΪ0������
����Inf������Ŀ��֤��ȷ�������û�г������ͷ�Χ��������

������func(m, n)�������Ƕ�m/n�ķ������л���gcd
(t1, t2)�������Ǽ���t1��t2�����Լ������func����
�У��ȿ�m��n�����Ƿ���0����m*n�Ƿ����0���������ĸ
n=0�����Inf���������m=0�������0�填flag��ʾm��n��
����ţ�flag=true��ʾ����Ҫ��Ӹ��š�(-�������š�)����
�ٽ�m��n��תΪabs(m)��abs(n)����ȡ���ǵ��������ַ���
���㡫x = m/nΪm��n�Ŀ���ȡ���������֣��ȸ���flag�Ľ�
���ж��Ƿ�Ҫ��ǰ��׷�ӡ�(-����Ȼ�����x�Ƿ����0�ж�Ҫ��
Ҫ����������λ�����Ÿ���m%n�Ƿ����0�Ľ���жϺ��滹
��û��С���������m�ܱ�n��������ʾû�к����С��������
ô�͸���flag�Ľ���ж�Ҫ��Ҫ�ӡ�)����Ȼ��ֱ��return����
��������λ���Һ�����С��������Ҫ�����һ���ո񣬽��Ŵ�
��ʣ�µ�С�������Ȱ�m���Ӽ�ȥ�Ѿ���ȡ�����������֣�
Ȼ����m��n�����Լ��t����m��n������t���л������
�����m/n�������flag==true��Ҫ��ĩβ�����)��

ע�⣺�ж�m��n�Ƿ����ǧ��Ҫд���ж�m*n�Ƿ�С��0
����Ϊm*n�Ľ�����ܳ�����long long int�ĳ��ȣ�����
�������0���������д�Ļ�����һ�����Ե��޷�ͨ������(
��o��)��Ϊ����һ�����Ե���bug�ҵ��賿������ľ����ҡ�
�Һò˰�.jpg��
*/
//#include <iostream>
//#include <cmath>
//#include<stdio.h>
//using namespace std;
//long long a, b, c, d;
//long long gcd(long long t1, long long t2) {
//	return t2 == 0 ? t1 : gcd(t2, t1 % t2);
//}
//void func(long long m, long long n) {
//	if (m * n == 0) {
//		printf("%s", n == 0 ? "Inf" : "0");
//		return;
//	}
//	bool flag = ((m < 0 && n > 0) || (m > 0 && n < 0));
//	m = abs(m); n = abs(n);
//	long long x = m / n;
//	printf("%s", flag ? "(-" : "");
//	if (x != 0) printf("%lld", x);
//	if (m % n == 0) {
//		if (flag) printf(")");
//		return;
//	}
//	if (x != 0) printf(" ");
//	m = m - x * n;
//	long long t = gcd(m, n);
//	m = m / t; n = n / t;
//	printf("%lld/%lld%s", m, n, flag ? ")" : "");
//}
//int main() {
//	scanf("%lld/%lld %lld/%lld", &a, &b, &c, &d);
//	func(a, b); printf(" + "); func(c, d); printf(" = "); func(a * d + b * c, b * d); printf("\n");
//	func(a, b); printf(" - "); func(c, d); printf(" = "); func(a * d - b * c, b * d); printf("\n");
//	func(a, b); printf(" * "); func(c, d); printf(" = "); func(a * c, b * d); printf("\n");
//	func(a, b); printf(" / "); func(c, d); printf(" = "); func(a * d, b * c);
//	return 0;
//}

/////////////////////////////////////////////////////////////////////////////////////////
//���ӣ�https://www.nowcoder.com/questionTerminal/89844f1f632c475ab6f4a600f71683a8
//��Դ��ţ����

//m�������ڵ㺢�ӽ�����Ϊn,���Եõ������C(m,n)���ݹ���ø��ڵ�ĸ������ӽڵ�Ϊ��
//������,�õ�n�������.��n��������������C(m,n)�ĺͼ�Ϊ�������������***��������
//�ܸ���
//����ÿ���׶μ�����������÷ֶ���֮��˼�룬��ȶ������������ݹ���õ�����ķ�ʽ
//���Խ�����ͺ����Ϊn��������Ӧ��������������У�ͳ�������еĸ�����Ϊ�ɵõ�n��
#include<cstdio>
(802)#include<cstring>
#include<map>
using namespace std;
char pre[30], post[30];
int m;
map<char, int> mp;
int ccal(int n1, int m1){
	int sum = 1;
	for (int i = 1; i <= m1; ++i){
		sum = sum*(n1 - m1 + i) / i;
	}
	return sum;
}
int cal(int pl, int pr, int pol, int ***bsp;   if (pl >= pr){
	return 1;
}
int ans = 1, i = pl + 1, l = pol, r = mp[pre[pl + 1]];
int sum = 0;
while (i <= pr){
	ans *= cal(i, i + r - l, l, r);
	sum++;
	i = i + r - l + 1;
	l = r + 1;
	if (i <= pr)
		r = mp[pre[i]];
}
ans *= ccal(m, sum);
return ans;
}
int main(){
	while (scanf("%d %s %s", &m, pre, post) != EOF){
		int len = strlen(pre);
		mp.clear();
		for (int i = 0; i<strlen(post); ++i){
			mp[post[i]] = i;
		}
		int cnt = cal(0, len - 1, 0, len - 1);
		printf("%d\n", cnt);
	}
	return 0;
}

