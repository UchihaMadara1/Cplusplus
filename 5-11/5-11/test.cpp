#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>
#include<stack>
#include<vld.h>

using namespace std;

template <class Type>
class AVLTree;

template <class Type>
class AVLNode
{
	friend class AVLTree<Type>;
public:
	AVLNode(Type _data = Type(), AVLNode<Type> *left = nullptr,
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
	{
		if (root != nullptr)
			Destroy(root);
	}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
public:
	void RotateL(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subL = ptr;
		ptr = ptr->rightchild;
		subL->rightchild = ptr->leftchild;
		ptr->leftchild = subL;

		ptr->bf = subL->bf = 0;
	}
	void RotateR(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subR = ptr;
		ptr = ptr->leftchild;
		subR->leftchild = ptr->rightchild;
		ptr->rightchild = subR;

		ptr->bf = subR->bf = 0;
	}
	void RotateLR(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subR = ptr;
		AVLNode<Type> *subL = ptr->leftchild;
		ptr = subL->rightchild;
		//左旋转
		subL->rightchild = ptr->leftchild;
		ptr->leftchild = subL;
		//bf
		if (ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		//左旋转
		subR->leftchild = ptr->rightchild;
		ptr->rightchild = subR;
		//bf
		if (ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;

		ptr->bf = 0;
	}
	void RotateRL(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subL = ptr;
		AVLNode<Type> *subR = ptr->rightchild;
		ptr = subR->leftchild;
		//右旋转
		subR->leftchild = ptr->rightchild;
		ptr->rightchild = subR;
		//bf
		if (ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;
		//左旋转
		subL->rightchild = ptr->leftchild;
		ptr->leftchild = subL;
		//bf

		if (ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		ptr->bf = 0;
	}
protected:
	bool Insert(AVLNode<Type> *&root, const Type &x);
	void Destroy(AVLNode<Type> *&root);
private:
	AVLNode<Type> *root;
};

//方法实现
template <class Type>
bool AVLTree<Type>::Insert(AVLNode<Type> *&t, const Type &x)
{
	//按照AVL规则插入节点
	AVLNode<Type> *pr = nullptr;
	AVLNode<Type> *p = t;
	stack<AVLNode<Type>*> st;
	while (p != nullptr)
	{
		if (x == p->data)
			return false;

		pr = p;
		st.push(pr);
		if (x < p->data)
			p = p->leftchild;
		else
			p = p->rightchild;
	}
	p = new AVLNode<Type>(x);
	if (pr == nullptr)
	{
		t = p;
		return true;
	}
	//链接节点
	if (p->data > pr->data)
		pr->rightchild = p;
	else
		pr->leftchild = p;

	//平衡节点
	while (!st.empty())
	{
		pr = st.top();
		st.pop();
		if (p == pr->leftchild)
			pr->bf--;
		else
			pr->bf++;

		if (pr->bf == 0)
			break;
		else if (pr->bf == 1 || pr->bf == -1)
			p = pr;
		else
		{
			//旋转调整
			if (pr->bf > 0)
			{
				if (p->bf > 0)
				{
					//RotateL \ 
					RotateL(pr);
				}
				else
				{
					//RotateRL
					RotateRL(pr);
				}
			}
			else
			{
				if (p->bf < 0)
				{
					//RotateR
					RotateR(pr);
				}
				else
				{
					//RotateLR
					RotateLR(pr);
				}
			}
			break;
		}
	}
	//重新对pr连接父节点

	if (st.empty())
	{
		t = pr;
	}
	else
	{
		AVLNode<Type> *ppr = st.top();
		if (ppr->data > pr->data)
			ppr->leftchild = pr;
		else
			ppr->rightchild = pr;
	}

	return true;
}

//摧毁AVL树
template<class Type>
void AVLTree<Type>::Destroy(AVLNode<Type> *&t)
{
	if (t == nullptr)
		return;
	if (t->leftchild == nullptr&&t->rightchild == nullptr)
	{
		delete t;
		t = nullptr;
		return;
	}
	Destroy(t->leftchild);
	t->leftchild = nullptr;
	Destroy(t->rightchild);
	t->rightchild = nullptr;
	delete t;
	t = nullptr;
}

int main()
{
	AVLTree<int> avl;
	vector<int> iv = { 3, 7, 10, 5, 20, 13, 15, 19, 23, 14 };
	for (const auto &e : iv)
		avl.Insert(e);

	cout << "Destroy begin..."<<endl;
	return 0;
}
