#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>


using namespace std;

////碰到\n则刷新一次输出缓冲期权
////printf函数是从右往左运算的：打印时先把数据的地址放在缓冲区，输出时
////把数据压入栈内，然后依次出栈
////前置++是运算当前对象后返回本对象，而后置++是先构建一个临时对象，再对本对象++后返回临时对象.
////所以  输出缓冲区会保存两个变量的地址,即本对象的地址和后置++构建的临时对象的地址。
////把数据加载到缓冲区和压栈出栈的过程是分开的。
//int main()
//{
//	int i = 1;
//	printf("%d %d\n",++i,++i);
//	printf("%d %d\n",++i,i++);
//	return 0;
//}



/*
//CPU 有不同位数 16 32 64 字长 ：在同一时间CPU处理二进制的位数叫字长  处理字长为 8 8位CPU 32
//字长反应了这个计算机的精度  cpu 寻址
// 字节 （内存最小寻址单位）  一个指针的地址值对应内存中一个字节空间 32
//寻址空间CPU对于内存寻址的能力 32 位CPU 2^32 4G地址
//寻址位数是由地址总线位数决定的 32寻址CPU 地址就是一个32位二进制数 （4Byte） 4个字节指针
//指针大小是由CPU寻址位数决定，不是字长

//编译器处理模式 32 64  CLion
*/

//在同一地址总线下，指针的大小是完全相同的。但是不同类型指针每次访问数据时跳转的字节数是不一样的。
int main()
{
	long a = (long)((char*)0 + 4);
	long b = (long)((int *)0 + 4);
	long c = (long)((double*)0 + 4);
	printf("%d %d %d",a,b,c);
	cout << endl;
	return 0;
}