#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>

using namespace std;

typedef enum COLOR{ RED = 0, BLACK = 1 }COLOR_Type;

template <class Type>
class RBTreeNode
{
	friend class RBTree<Type>;
public:
	RBTreeNode(Type &_data = Type()) :leftchild(nullptr), rightchild(nullptr)
		parent(nullptr), COLOR(RED)
	{}
	~RBTreeNode()
	{}
private:
	Type data;
	RBTreeNode<Type> *leftchild;
	RBTreeNode<Type> *rightchild;
	RBTreeNode<Type> *parent;
	COLOR_Type color;
};

template<class Type>
class RBTree
{
public:
	RBTree() :root(NIL), NIL(_buyNode())
	{
		NIL->parent = ->leftchild = NIL->rightchild = nullptr;
		NIL->COLOR = BLACK;
	}
	~RBTree()
	{}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
protected:
	RBTreeNode<Type> *_buyNode(const Type &x = Type())
	{
		RBTreeNode<Type> *s = new RBTreeNode<Type>(x);
		s->leftchild = s->rightchild = NIL;
		return s;
	}
protected:
	void RightRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p)
	{
		if (p->parent = NIL)
			t = p->leftchild;
		RBTreeNode<Type> *subL = p->leftchild;

	}

protected:
	bool Insert(RBTreeNode<Type> *t, const Type &x);
	void Insert_Fixup(RBTreeNode<Type> *&t, RBTreeNode<Type> *s);
private:
	RBTreeNode<Type> *NIL;
	RBTreeNode<Type> *root;
};

template<class Type>
bool RBTree<Type>::Insert(RBTreeNode<Type> *t, const Type &x)
{
	RBTreeNode<Type> *pr = NIL;
	RBTreeNode<Type> *p = t;
	while (p != NIL)
	{
		if (x == p->data)
			return false;
		pr = p;
		if (p->data > x)
			p = p->leftchild;
		else
			p = p->rightchild;
	}
	p = _buyNode(x);
	if (pr == NIL)
	{
		t = p;
		return true;
	}
	else if (pr->data > x)
		pr->leftchild = p;
	else
		pr->rightchild = p;
	p->parent = pr;

	//调整平衡
	Insert_Fixup(t, p);

	return true;
}

template<class Type>
void RBTree<Type>::Insert_Fixup(RBTreeNode<Type> *&t, RBTreeNode<Type> *x)
{
	while (x->parent->color == RED)
	{
		RBTreeNode<Type> *s;
		if (x->parent = x->parent->parent->leftchild)//左分支
		{
			s = x->parent->parent->rightchild;
			if (s->color == RED)
			{
			}
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			RightRotate(t,x->parent->parent);
		}
		else//右分支
		{

		}
	}
	t->color = BLACK;
}


int main()
{
	vector<int> iv = { 12, 34, 5, 678, 23, 87, 4, 98, 19 };
	RBTree<int> rb;
	for (auto &e : iv)
		rb.Insert(e);
	return 0;
}

