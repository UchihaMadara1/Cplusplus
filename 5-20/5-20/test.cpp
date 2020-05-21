#define _CRT_SECURE_NO_WARNINGS

//哈夫曼数主要用于编码和压缩

#include<iostream>
#include<algorithm>
using namespace std;
//哈夫曼编码 一般的实现时邻接表或者邻接矩阵
	int i1;
	int i2;
	typedef struct HuffNode
	{
		int weigit;//权值
		int lchild;
		int rchild;
		int parent;
	}HuffNode;
	//每次搜索parent为-1最小的值
	void Select(HuffNode huffTree[], int k, int &i1, int &i2);
	void HuffmanTree(HuffNode huffTree[], int w[], int n)//w是权值数组，叶子节点个数n 哈夫曼树构建
	{
		for (int i = 0; i < 2 * n - 1; i++)//将所有的节点值赋值为-1
		{
			huffTree[i].parent = -1;
			huffTree[i].lchild = -1;
			huffTree[i].rchild = -1;
		}
		for (int i = 0; i < n; i++) //给权值赋值
		{
			huffTree[i].weigit = w[i];
		}
		for (int k = n; k < 2 * n - 1; k++)//构建哈夫曼树 0~n-1
		{

			Select(huffTree, k, i1, i2);//找到parent为-1的最小和次小节点  存入il i2;
			huffTree[k].weigit = huffTree[i1].weigit + huffTree[i2].weigit;
			huffTree[i1].parent = k;
			huffTree[i2].parent = k;
			huffTree[k].lchild = i1;
			huffTree[k].rchild = i2;
		}
	}
	int temp1;
	int temp2;
	void Select(HuffNode huffTree[], int k, int& i1, int& i2)
	{
		int i = 0;
		i1 = INT_MAX;
		i2 = INT_MAX;//找一个权值不可能出现的值出来
		for (i; i < k; ++i)
		{
			if (huffTree[i].weigit < i1 &&huffTree[i].parent == -1)
			{
				i1 = huffTree[i].weigit;//找到最小的元素了
				temp1 = i;
			}
		}
		for (int j = 0; j < k; ++j)
		{
			if (huffTree[j].weigit < i2 && j != temp1 && huffTree[j].parent == -1)
			{
				i2 = huffTree[j].weigit;
				temp2 = j;
			}
		}
		i1 = temp1;
		i2 = temp2;
	}
	//a b c d 出现频率是 2 4 5 3 求哈哈夫曼编码

	//具体体现为 对于 a b c d进行编码 然后给出编码情况
	void huffmanCoding(char* HuffCode[], HuffNode huffTree[], int n)//这个n是哈夫曼编码的个数  
	{
		char* temp = new char[n];
		temp[n - 1] = '\0';
		for (int i = 0; i < n; ++i)//为啥是n而不是 2*n-1呢?因为我们只需要看叶子节点就行，没必要把所有的都遍历一遍
		{
			int start = n - 1;
			int pos = i;
			int parent = huffTree[i].parent;
			while (parent != -1)
			{
				if (huffTree[parent].lchild == pos)
					temp[--start] = '0';
				else
					temp[--start] = '1';
				pos = parent;
				parent = huffTree[parent].parent;
			}
			HuffCode[i] = new char[n - start];//这是个指针数组
			strcpy(HuffCode[i], &temp[start]);
		}
		delete temp;
	}
	/*
	int main()
	{
	int num = 3;
	int arr[] = { 1,2,5};
	HuffNode huff[5];
	HuffmanTree(huff, arr, num);
	for (int i = 0; i < 5; ++i)
	{
	cout << huff[i].weigit << " " << huff[i].parent << " " << huff[i].lchild << " " << huff[i].rchild;
	cout << endl;
	}
	system("pause");
	return 0;
	}
	*/






	//哈夫曼树的构建没有问题

	/*int main()
	{
	//A B C的出现次数是1 2 5
	int num = 3;
	int arr[] = { 1,2,5};
	HuffNode huff[5];
	HuffmanTree(huff, arr, num);
	for (int i = 0; i < 5; ++i)
	{
	cout << huff[i].weigit << " " << huff[i].parent << " " << huff[i].lchild << " " << huff[i].rchild;
	cout << endl;
	}
	cout << "______________________________________________________________________________" << endl;
	char* code[3];
	huffmanCoding(code, huff, num);
	for (int i = 0; i < 3; ++i)
	{
	printf("%s\n", code[i]);
	}
	system("pause");
	return 0;
	}

	*/

	/*
	int temp;
	int main()
	{
	int arr[] = { 1,2,3,4,21,58,7,96,2,56 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	int max = arr[0];
	int max1 = -100;
	if (sz == 1)
	max = max1 = arr[0];
	for (int i = 0; i < sz; ++i)
	{
	if (arr[i] > max)
	{
	temp = i;// 记录位置
	max = arr[i];
	}
	}
	for (int j = 0; j < sz; ++j)
	{
	if (arr[j] > max1&& j != temp)
	max1 = arr[j];
	}
	cout << "max = " << max << "max1 = " << max1 << endl;

	system("pause");
	return 0;
	}



	int temp;
	int main()
	{
	//如何来找到最大和第二大不用排序
	int arr[] = { 1,2,3,4,21,58,7,96,2,56};
	int sz = sizeof(arr) / sizeof(arr[0]);
	int i = 0;
	int max;
	int max1;
	if (sz == 1)
	max = max1 = arr[0];
	for (i; i < sz-1; ++i)
	{
	if (arr[i] > arr[i + 1])
	{
	max = arr[i];
	temp = i;//记录最大数的位置
	}
	else
	{
	max = arr[i+1];
	temp = i + 1;
	}
	}
	for (int j = 0; j < sz; ++j)
	{
	if (j != sz - 1)
	{
	if (arr[j] > arr[j + 1] && j != temp)
	{
	max1 = arr[j];
	}
	if (arr[j] < arr[j + 1] && j + 1 != temp)
	{
	max1 = arr[j + 1];
	}
	}
	else if(j != temp && j == sz-1)//最后一个数
	{
	max1 = arr[j] > max1 ? arr[j] : max1;
	}

	}
	cout << "max = " << max << "max1 = " << max1 << endl;

	system("pause");
	return 0;
	}
	*/

	int main()
	{
		int a = 1 && 2 && 3 || 4;
		cout << a << endl;

		system("pause");
		return 0;
	}
