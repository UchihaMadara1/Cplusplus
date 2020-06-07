#define _CRT_SECURE_NO_WARNINGS
/*
题目大意：输入在一行中按照“a1/b1 a2/b2”的格式给出两个分数形式的有理数，
其中分子和分母全是整型范围内的整数，负号只可能出现在分子前，分母不为0，
分别在4行中按照“有理数1 运算符 有理数2 = 结果”的格式顺序输出2个有理数的
和、差、积、商。注意输出的每个有理数必须是该有理数的最简形式“k a/b”，其中
k是整数部分，a/b是最简分数部分；若为负数，则须加括号；若除法分母为0，则输
出“Inf”～题目保证正确的输出中没有超过整型范围的整数～

分析：func(m, n)的作用是对m/n的分数进行化简，gcd
(t1, t2)的作用是计算t1和t2的最大公约数～在func函数
中，先看m和n里面是否有0（即m*n是否等于0），如果分母
n=0，输出Inf，如果分子m=0，输出”0″～flag表示m和n是
否异号，flag=true表示后面要添加负号”(-“和括号”)”，
再将m和n都转为abs(m)和abs(n)，即取他们的正数部分方便
计算～x = m/n为m和n的可提取的整数部分，先根据flag的结
果判断是否要在前面追加”(-“，然后根据x是否等于0判断要不
要输出这个整数位，接着根据m%n是否等于0的结果判断后面还
有没有小分数，如果m能被n整除，表示没有后面的小分数，那
么就根据flag的结果判断要不要加”)”，然后直接return～如
果有整数位，且后面有小分数，则要先输出一个空格，接着处
理剩下的小分数，先把m分子减去已经提取出的整数部分，
然后求m和n的最大公约数t，让m和n都除以t进行化简～最后
输出“m/n”，如果flag==true还要在末尾输出”)”

注意：判断m和n是否异号千万不要写成判断m*n是否小于0
，因为m*n的结果可能超过了long long int的长度，导致
溢出大于0，如果这样写的话会有一个测试点无法通过～（(
⊙o⊙)嗯为了这一个测试点找bug找到凌晨两三点的就是我…
我好菜啊.jpg）
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
//链接：https://www.nowcoder.com/questionTerminal/89844f1f632c475ab6f4a600f71683a8
//来源：牛客网

//m叉树根节点孩子结点个数为n,可以得到组合数C(m,n)，递归调用根节点的各个孩子节点为根
//的子树,得到n个组合数.这n个组合数与组合数C(m,n)的和即为以先序与后序序***定的树的
//总个数
//其中每个阶段计算组合数采用分而治之的思想，类比二叉树先序后序递归调用得中序的方式
//可以将先序和后序分为n个子树对应的先序后序子序列，统计子序列的个数即为可得到n，
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

