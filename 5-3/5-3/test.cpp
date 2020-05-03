#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
}
	
};
class Solution {
public:
	bool Find(int target, vector<vector<int> > array)
	{
		int i = 0;
		int j = array[i].size() - 1;
		while (i < array.size() && j >= 0)
		{
			if (target == array[i][j])
				return true;
			else if (target < array[i][j])
				j--;
			else if (target > array[i][j])
				i++;
		}
		return false;
	}
public:
	void replaceSpace(char *str, int length)
	{
		string s(str);
		int i = 0;
		while ((i = s.find(' ', i)) > -1)
		{
			s.erase(i, 1);
			s.insert(i, "%20");
		}
		auto ret = s.c_str();
		strcpy(str, ret);
	}
public:
	vector<int> printListFromTailToHead(ListNode* head)
	{
		ListNode *p = head;
		ListNode *q = head;
		vector<int> v;
		while (p != NULL)
			p = p->next;
		while (p != head)
		{
			while (q->next != p)
				q = q->next;
			v.push_back(q->val);
			p = q;
			q = head;
		}
		return v;
	}
};
