#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<assert.h>

using namespace std;

#define N 100

typedef int DataType;

//typedef struct SeqList
//{
//	DataType array[N];
//	size_t size;
//}SeqList;

typedef struct SqeList
{
	DataType *array;
	size_t size;
	size_t capacity;
}SeqList;

// 基本增删查改接口
void SeqListInit(SeqList* psl, size_t capacity);
void SeqListDestory(SeqList* psl);
void CheckCapacity(SeqList* psl);
void SeqListPushBack(SeqList* psl, DataType x);
void SeqListPopBack(SeqList* psl);
void SeqListPushFront(SeqList* psl, DataType x);
void SeqListPopFront(SeqList* psl);
int SeqListFind(SeqList* psl, DataType x);
void SeqListInsert(SeqList* psl, size_t pos, DataType x);
void SeqListErase(SeqList* psl, size_t pos);
void SeqListRemove(SeqList* psl, DataType x);
void SeqListModify(SeqList* psl, size_t pos, DataType x);
void SeqListPrint(SeqList* psl);
// 扩展面试题实现
void SeqListBubbleSort(SeqList* psl);
int SeqListBinaryFind(SeqList* psl, DataType x);
// 本题要求：时间复杂度：O(N) 空间复杂度 O(1)
void SeqListRemoveAll(SeqList* psl, DataType x);

void SeqListInit(SeqList* psl, size_t capacity)
{
	psl->array = (DataType*)malloc(sizeof(DataType)* capacity);
	memset(psl->array, 0, capacity);
	psl->capacity = capacity;
	psl->size = 0;
}
void SeqListDestory(SeqList* psl)
{
	assert(psl != NULL);
	psl->capacity = psl->size = 0;
	free(psl->array);
	psl->array = NULL;
}
void CheckCapacity(SeqList* psl)
{
	assert(psl != NULL);
	psl->array = (DataType*)realloc(psl->array, psl->capacity + 2);
	psl->capacity += 2;
	memset(psl->array, 0, psl->capacity);
}
void SeqListPushBack(SeqList* psl, DataType x)
{
	assert(psl != NULL);
	while (psl->size >= psl->capacity)
	{
		CheckCapacity(psl);
	}
	psl->array[psl->size++] = x;
}
void SeqListPopBack(SeqList* psl)
{
	assert(psl != NULL);
	if (psl->size == 0)
		return;
	psl->size--;
}
void SeqListPushFront(SeqList* psl, DataType x)
{
	assert(psl != NULL);
	while (psl->size >= psl->capacity)
	{
		CheckCapacity(psl);
	}
	if (psl->size == 0)
	{
		psl->array[psl->size++] = x;
		return;
	}
	psl->size++;
	for (size_t i = 1; i < psl->size; ++i)
	{
		psl->array[i] = psl->array[i - 1];
	}
	psl->array[0] = x;
}
void SeqListPopFront(SeqList* psl)
{
	assert(psl != NULL);
	if (psl->size == 0)
		return;
	for (size_t i = 0; i < psl->size - 1; ++i)
	{
		psl->array[i] = psl->array[i + 1];
	}
	psl->size--;
}
int SeqListFind(SeqList* psl, DataType x)
{
	assert(psl != NULL);
	for (size_t i = 0; i < psl->size; ++i)
	{
		if (x == psl->array[i])
			return i;
	}
	return -1;
}
void SeqListInsert(SeqList* psl, size_t pos, DataType x)
{
	assert(psl != NULL);
	if (psl->size >= psl->capacity)
	{
		CheckCapacity(psl);
	}
	if (pos < psl->size)
	{
		for (size_t i = pos - 1; i <= psl->size; ++i)
			psl->array[i + 1] = psl->array[i];
		psl->array[pos] = x;
	}
	else
	{
		psl->array[psl->size] = x;
	}
	psl->size++;
}
void SeqListErase(SeqList* psl, size_t pos)
{
	assert(psl != NULL);
	if (pos > psl->size)
		return;
	for (size_t i = pos - 1; i < psl->size - 1; ++i)
	{
		psl->array[i] = psl->array[i + 1];
	}
	psl->size--;
}
void SeqListRemove(SeqList* psl, DataType x)
{
	assert(psl != NULL);
	int pos = SeqListFind(psl, x) + 1;
	SeqListErase(psl, pos);
}
void SeqListModify(SeqList* psl, size_t pos, DataType x)
{
	assert(psl != NULL);
	if (pos <= psl->size)
		psl->array[pos - 1] = x;
	else
	{
		SeqListPushBack(psl, x);
	}
}
void SeqListPrint(SeqList* psl)
{
	assert(psl != NULL);
	for (size_t i = 0; i < psl->size; ++i)
	{
		cout << psl->array[i] << " ";
	}
}
int main()
{
	SeqList *psl = NULL;
	int capacity = 5;
	//SeqListInit(&sql,5);
	//SeqListPushBack(&sql,1);
	int pos = 5, x = 12;
	SeqListInit(psl, capacity);
	SeqListDestory(psl);
	CheckCapacity(psl);
	SeqListPushBack(psl, x);
	SeqListPopBack(psl);
	SeqListPushFront(psl, x);
	SeqListPopFront(psl);
	SeqListFind(psl, x);
	SeqListInsert(psl, pos, x);
	SeqListErase(psl, pos);
	SeqListRemove(psl, x);
	SeqListModify(psl, pos, x);
	SeqListPrint(psl);
	return 0;
}
