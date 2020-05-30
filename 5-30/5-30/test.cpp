#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stack>
#include<vector>

using namespace std;


struct TreeNode 
{
    int val;
	TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



class solution
{
public:
	int minNumberInRotateArray(vector<int> rotateArray)
	{
		int left = 0, right = rotateArray.size() - 1, mid = 0;
		while (left < right)
		{
			mid = left + (right - left) / 2;
			if (rotateArray[mid] > rotateArray[right])
				left = mid + 1;
			else if (rotateArray[mid] == rotateArray[right])
				right--;
			else
				right = mid;
		}
		return rotateArray[left];
	}
	public:
		void push(int node)
		{
			stack1.push(node);
		}

		int pop()
		{
			int a;
			if (stack2.empty())
			{
				while (!stack1.empty())
				{
					a = stack1.top();
					stack2.push(a);
					stack1.pop();
				}
			}
			a = stack2.top();
			stack2.pop();
			return a;
		}
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		if (pre.size() == 0)
			return NULL;
		TreeNode *root = new TreeNode(pre[0]);
		int i;
		for (i = 0; i < vin.size() && vin[i] != pre[0]; ++i);
		vector<int> pre_left, vin_left, pre_right, vin_right;
		int pre_i = 1;
		for (int j = 0; j < vin.size(); ++j)
		{
			if (j < i)
			{
				vin_left.push_back(vin[j]);
				pre_left.push_back(pre[pre_i]);
				pre_i++;
			}
			else if (j > i)
			{
				vin_right.push_back(vin[j]);
				pre_right.push_back(pre[pre_i]);
				pre_i++;
			}
		}
		root->left = reConstructBinaryTree(pre_left, vin_left);
		root->right = reConstructBinaryTree(pre_right, vin_right);
		return root;
	}
	private:
		stack<int> stack1;
		stack<int> stack2;

};
int main()
{
	return 0;
}
