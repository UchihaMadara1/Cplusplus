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
//
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
	psl->array = (DataType*)malloc(sizeof(DataType) * capacity);
	memset(psl->array,0,capacity);
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
	psl->array = (DataType*)realloc(psl->array,psl->capacity + 2);
	psl->capacity += 2;
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
	for (int i = 1; i < psl->size; ++i)
	{
		psl->array[i] = psl->array[i - 1];
	}
	psl->array[0] = x;
}
int main()
{
	SeqList sql;
	SeqListInit(&sql,5);
	SeqListPushBack(&sql,1);
	return 0;
}