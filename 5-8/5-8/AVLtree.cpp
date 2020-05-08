#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<stack>

using namespace std;

template <class Type>
class AVLTree;

template <class Type>
class AVLNode
{
public:
	AVLNode(Type _data = Type(),AVLNode<Type> *left = nullptr,
		AVLNode<Type> *right = nullptr) :data(_data),
		leftchild(left), rightchild(right), bf(0)
	{}
	~AVLNode()
	{}
public:

private:
	Type          data;
	AVLNode<Type> *leftchild;
	AVLNode<Type> *rightchild;
	int           bf;//平衡因子 0 1 -1 2 -2
};
template <class Type>
class AVLTree
{
public:
	AVLTree() :root(nullptr)
	{}
	~AVLTree()
	{}
public:
	bool Insert(const Type &x)
	{
		return Insert(root,x);
	}
protected:
	bool Insert(AVLNode<Type> *&root, const Type &x);
private:
	AVLNode<Type> *root;
};

//方法实现
template <class TYpe>
bool AVLTree::Insert(AVLNode<Type> *&root, const Type &x)
{
	if (root == nullptr)
	{
		root->data = x;
		return true;
	}
	if (x > root->data)
		Insert(root->rightchild);
	else if (x < root->data)
		Insert(root->leftchild);
	else
		return false;
}
int main()
{
	AVLTree<int> avl;
	vector<int> iv = {10,7,3,5,20,13,15,19,23,14};
	for (const auto &e : iv)
		avl.Insert(e);
	return 0;
}