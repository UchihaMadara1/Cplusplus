#define _CRT_SECURE_NO_WARNINGS 

#include<iostream>

using namespace std;
//环形链表 
//手撕环形链表判断一个链表是否有环

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	bool hasCycle(ListNode *head) {
		if (head == NULL || head->next == NULL)   //一个节点且无环或者没有节点
			return false;
		ListNode *fast = head;//head->next
		ListNode *slow = head->next;//
		while (fast != slow) {
			if (fast->next == NULL || fast->next->next == NULL)//slow 
				return false;
			fast = fast->next->next;
			slow = slow->next;
		}
		return true;
	}
};

//返回链表的相遇点

class Solution1 {
public:
	ListNode *detectCycle(ListNode *head) {
		//是否有环
		if (head == NULL || head->next == NULL)
			return NULL;
		ListNode * p = head;
		ListNode * q = head;
		while (q != NULL && q->next != NULL)//第一次pq相遇
		{
			p = p->next;
			q = q->next->next;
			if (p == q)
				break;
		}

		if (p == q)
		{
			p = head;
			while (p != q)//从起点开始，在入口点相遇
			{
				p = p->next;
				q = q->next;
			}
			return p;
		}

		return NULL;
	}
};
int main()
{
	ListNode mylist(3);
	ListNode mylist1(5);
	ListNode mylist2(5);
	mylist.next = &mylist1;
	mylist1.next = &mylist2;
	mylist2.next = &mylist1;
	mylist.next = &mylist;
	Solution a;
	cout << a.hasCycle(&mylist) << endl;
	system("pause");
	return 0;
}
/*
给定一个链表，返回链表开始入环的第一个节点。?如果链表无环，则返回?null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 - 1，则在该链表中没有环。
*/


int main()
{

	system("pause");
	return 0;
}