#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<assert.h>

using namespace std;

typedef int DataType;
typedef struct SListNode
{
	DataType data;
	struct SListNode *next;
}SListNode;

typedef struct SList
{
	SListNode *first;
	SListNode *end;
	size_t size;
}SList;

void SListInit(SList* plist);
void SListDestory(SList* plist);
SListNode* BuySListNode(DataType x);

SListNode* BuySListNode(DataType x)
{
	SListNode *s = (SListNode*)malloc(sizeof(SListNode));
	if (s == NULL)
	{
		cout << "buynode error..." << endl;
		return NULL;
	}
	s->data = x;
	s->next = NULL;
	return s;
}
void SListInit(SList* plist)
{
	assert(plist);
	SListNode *s = BuySListNode(-1);
	if (s == NULL)
		return;
	plist->first = plist->end = s;
	plist->size = 0;
}
void SListDestory(SList* plist)
{
	assert(plist);
	SListNode *s = plist->first;
	if (s == NULL)
		return;
	while (s != NULL)
	{
		plist->first = s->next;
		free(s);
		s = plist->first;
	}
	plist->size = 0;
	plist->end = NULL;
}
bool SListPushFront(SList* plist, DataType x);
bool SListPopFront(SList* plist);
SListNode* SListFind(SList* plist, DataType x);
bool SListPushBack(SList *plist,DataType x);

bool SListPushBack(SList *plist, DataType x)
{
	assert(plist);
	SListNode *s = BuySListNode(x);
	if (s == NULL)
		return false;
	plist->end->next = s;
	plist->end = s;
	plist->size++;
	return true;
}
bool SListPushFront(SList* plist, DataType x)
{
	assert(plist);
	SListNode *s = BuySListNode(x);
	if (s == NULL)
		return false;
	if (plist->first->next == NULL)
	{
		plist->first->next = s;
		plist->end = s;
		plist->size++;
		return true;
	}
	s->next = plist->first->next;
	plist->first->next = s;
	plist->size++;
	return true;
}
bool SListPopFront(SList* plist)
{
	assert(plist);
	SListNode *s = plist->first->next;
	if (s == NULL)
		return false;
	if (plist->end == s)
		plist->end = plist->first;
	plist->first->next = s->next;
	free(s);
	s = NULL;
	plist->size--;
	return true;;
}
SListNode* SListFind(SList* plist, DataType x)
{
	assert(plist);
	for (SListNode *s = plist->first->next; s != NULL; s = s->next)
	{
		if (s->data = x)
			return s;
	}
	return NULL;
}

// 在pos的后面进行插入
bool SListInsertAfter(SList* plist,size_t pos, DataType x);
bool SListEraseAfter(SList* plist,SListNode* pos);
void SListRemove(SList* plist, DataType x);
void SListPrint(SList* plist);
//
bool SListInsertAfter(SList* plist, int pos,DataType x)
{
	SListNode *s = plist->first;
	SListNode *p = BuySListNode(x);
	if (pos > plist->size)
		return false;
	for (int i = 0; i < pos; ++i)
	{
		s = s->next;
	}
	if (s == plist->end)
	{
		s->next = p;
		plist->end = p;
		return true;
	}
	p->next = s->next;
	s->next = p;
	plist->size++;
	return true;
}
bool SListEraseAfter(SList *plist,SListNode* pos)
{
	if (pos == NULL)
		return false;
	SListNode *s = pos->next;
	if (s == NULL)
		return false;
	pos->next = s->next;
	if (pos->next == NULL)
		plist->end = pos;
	free(s);
	s = NULL;
	plist->size--;
	return true;
}
void SListRemove(SList* plist, DataType x)
{
	assert(plist);
	SListNode *p = plist->first->next;
	for (SListNode *s = plist->first->next; s != NULL; s = s->next)
	{
		if (s->data == x)
		{
			if (s == plist->end)
			{
				while (p->next != s)
					p = p->next;
				p->next = NULL;
				free(s);
				s = NULL;
				plist->size--;
			}
			else
			{
				p = s->next;
				s->next = p->next;
				free(p);
				p = NULL;
				plist->size--;
			}
		}
	}
}
void SListPrint(SList* plist)
{
	assert(plist);
	for (SListNode *s = plist->first->next; s != NULL; s = s->next)
	{
		cout << s->data << "->";
	}
	cout << endl;
}
size_t GetSListSize(SList *plist)
{
	return plist->size;
}
bool SListIsEmpty(SList *plist)
{
	return plist->size == 0;
}
void SListReverse(SList *plist)
{
	assert(plist);
	if (plist->size < 2)
		return;
	SListNode *p1, *p2, *p3;
	p1 = NULL;
	p2 = plist->first->next;
	p3 = p2->next;
	plist->end = p2;
	while (p2 != NULL)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		if (p3 != NULL)
			p3 = p3->next;
	}
	plist->first->next = p1;
}
int main()
{
	return 0;
}