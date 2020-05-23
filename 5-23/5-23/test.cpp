#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<vector>

using namespace std;

typedef enum COLOR{ RED = 0, BLACK = 1 }COLOR_Type;

template <class Type>
class RBTree;

template <class Type>
class RBTreeNode
{
	friend class RBTree<Type>;
public:
	RBTreeNode(Type &_data = Type()) :leftchild(nullptr), rightchild(nullptr),
		parent(nullptr), color(RED)
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
		NIL->parent = NIL->leftchild = NIL->rightchild = nullptr;
		NIL->color = BLACK;
	}
	~RBTree()
	{}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
protected:
	RBTreeNode<Type> *_buyNode( Type x = Type())
	{
		RBTreeNode<Type> *s = new RBTreeNode<Type>(x);
		s->leftchild = s->rightchild = NIL;
		return s;
	}
protected:
	void RightRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p)
	{
		RBTreeNode<Type> *s = p->leftchild;
		p->leftchild = s->rightchild;
		if (s->leftchild != NIL)
			s->rightchild->parent = p;
		s->parent = p->parent;
		if (p->parent == NIL)
			t = s;
		else if (p->parent->leftchild == p)
			p->parent->leftchild = s;
		else
			p->parent->rightchild = s;
		s->rightchild = p;
		p->parent = s;
	}
	void LeftRotate(RBTreeNode<Type> *&t, RBTreeNode<Type> *p)
	{
		RBTreeNode <Type>*s = p->rightchild;
		p->rightchild = s->leftchild;
		if (s->leftchild != NIL)
			s->leftchild->parent = p;
		s->parent = p->parent;
		if (p->parent == NIL)
			t = s;
		else if (p->parent->leftchild == p)
			p->parent->leftchild = s;
		else
			p->parent->rightchild = s;
		s->leftchild = p;
		p->parent = s;
	}
protected:
	bool Insert(RBTreeNode<Type> *&t, const Type &x);
	void Insert_Fixup(RBTreeNode<Type> *&t, RBTreeNode<Type> *s);
private:
	RBTreeNode<Type> *NIL;
	RBTreeNode<Type> *root;
};

template<class Type>
bool RBTree<Type>::Insert(RBTreeNode<Type> *&t, const Type &x)
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
		t->parent = NIL;;
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
		if (x->parent == x->parent->parent->leftchild)//左分支
		{
			s = x->parent->parent->rightchild;
			if (s->color == RED)
			{
				//状况三
				x->parent->color = BLACK;
				s->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
				continue;
			}
			else if (x == x->parent->rightchild)
			{
				//状况二
				x = x->parent;
				LeftRotate(t,x);
			}
			//状况一
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			RightRotate(t, x->parent->parent);
		}
		else//右分支
		{
			s = x->parent->parent->leftchild;
			if (s->color == RED)
			{
				x->parent->color = BLACK;
				s->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
				continue;
			}
			else if (x == x->parent->leftchild)
			{
				//状况二
				x = x->parent;
				RightRotate(t,x);
			}
			//状况一
			x->parent->color = BLACK;
			x->parent->parent->color = RED;
			LeftRotate(t,x->parent->parent);
		}
	}
	t->color = BLACK;
}


int main()
{
	vector<int> iv = { 10,7,8,4,2,20,15,11,12,13 };
	RBTree<int> rb;
	for (const auto &e : iv)
		rb.Insert(e);
	return 0;
}


