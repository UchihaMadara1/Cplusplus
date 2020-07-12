#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

//¿ìËÙÅÅĞò
int get_mid(int arr[],int left,int right)
{
	int pivot = arr[left];
	while (left < right)
	{
		while (arr[right] >= pivot&&left < right)
			right--;
		arr[left] = arr[right];
		while (arr[left] <= pivot&&left < right)
			left++;
		arr[right] = arr[left];
	}
	arr[left] = pivot;
	return left;
}
void quick_sort(int arr[],int left,int right)
{
	if (left < right)
	{
		int mid = get_mid(arr, left, right);
		quick_sort(arr, left, mid - 1);
		quick_sort(arr, mid + 1, right);
	}
}
int main()
{
	int arr[] = {3,4,6,8,7,98,34,1,2,22};
	int right = sizeof(arr)/sizeof(arr[0]) - 1;
	int left = 0;
	quick_sort(arr, left, right);
	for (int i = 0; i <= right; ++i)
		cout << arr[i]<<" ";
	cout << endl;
	return 0;
}
