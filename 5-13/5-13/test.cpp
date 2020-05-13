#define _CRT_SECURE_NO_WARNINGS 

#include<iostream>

using namespace std;
//�������� 
//��˺���������ж�һ�������Ƿ��л�

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	bool hasCycle(ListNode *head) {
		if (head == NULL || head->next == NULL)   //һ���ڵ����޻�����û�нڵ�
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

//���������������

class Solution1 {
public:
	ListNode *detectCycle(ListNode *head) {
		//�Ƿ��л�
		if (head == NULL || head->next == NULL)
			return NULL;
		ListNode * p = head;
		ListNode * q = head;
		while (q != NULL && q->next != NULL)//��һ��pq����
		{
			p = p->next;
			q = q->next->next;
			if (p == q)
				break;
		}

		if (p == q)
		{
			p = head;
			while (p != q)//����㿪ʼ������ڵ�����
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
����һ��������������ʼ�뻷�ĵ�һ���ڵ㡣?��������޻����򷵻�?null��

Ϊ�˱�ʾ���������еĻ�������ʹ������ pos ����ʾ����β���ӵ������е�λ�ã������� 0 ��ʼ����
��� pos �� - 1�����ڸ�������û�л���
*/


int main()
{

	system("pause");
	return 0;
}