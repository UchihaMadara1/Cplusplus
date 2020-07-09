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
	AVLNode<Type> * _FrontLast(AVLNode<Type> *p,stack<AVLNode<Type> *> &sp)
	{
		AVLNode<Type> *q = p->leftchild;
		while(q ->rightchild != nullptr)
		{
			sp.push(q);
			q = q->rightchild;
		}
		return q;
	}
	AVLNode<Type> * _BcakLast(AVLNode<Type> *p,stack<AVLNode<Type> *> &sp)
	{
		AVLNode<Type> *q = p->rightchild;
		while (q->leftchild != nullptr)
		{
			sp.push(q);
			q = q->leftchild;
		}
		return q;
	}
private:
	Type          data;
	AVLNode<Type> *leftchild;
	AVLNode<Type> *rightchild;
	int           bf;//ƽ������ 0 1 -1 2 -2
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
	bool Delete(const Type &x)
	{
		return Delete(root,x);
	}
public:
	AVLNode<Type> *_Find(AVLNode<Type> *&root, Type &x)
	{
		AVLNode<Type> *t = root;
		while (t != nullptr)
		{
			if (t->data > x)
				t = t->leftchild;
			else if (t->data < x)
				t = t->rightchild;
			else
				break;
		}
		return t;
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
		//����ת
		subL->rightchild = ptr->leftchild;
		ptr->leftchild = subL;
		//bf
		if (ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		//����ת
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
		//����ת
		subR->leftchild = ptr->rightchild;
		ptr->rightchild = subR;
		//bf
		if (ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;
		//����ת
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
	bool Delete(AVLNode<Type> *&root,const Type &x);
	void Destroy(AVLNode<Type> *&root);
private:
	AVLNode<Type> *root;
};

//����ʵ��
template <class Type>
bool AVLTree<Type>::Insert(AVLNode<Type> *&t, const Type &x)
{
	//����AVL�������ڵ�
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
	//���ӽڵ�
	if (p->data > pr->data)
		pr->rightchild = p;
	else
		pr->leftchild = p;

	//ƽ��ڵ�
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
			//��ת����
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
	//���¶�pr���Ӹ��ڵ�

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
//ɾ���ڵ�
template<class Type>
bool AVLTree<Type>::Delete(AVLNode<Type> *&t, const Type &x)
{
	stack<AVLNode<Type> *> st;
	AVLNode<Type> *pr = nullptr;
	AVLNode<Type> *p = t;
	//���ҽڵ�
	while (p != nullptr)
	{
		if (p->data > x)
		{
			pr = p;
			st.push(pr);
			p = p->leftchild;
		}
		else if (p->data < x)
		{
			pr = p;
			st.push(pr);
			p = p->rightchild;
		}
		else
			break;
	}
	if (p == nullptr)
		return false;

	//ɾ���ڵ�'
	AVLNode<Type> *q;
	if (p->leftchild != nullptr&&p->rightchild != nullptr)
	{
		pr = p;
		st.push(pr);
		q = p->rightchild;
		while (q->leftchild != nullptr)
		{
			pr = q;
			st.push(pr);
			q = q->leftchild;
		}
		p->data = q->data;
		p = q;
	}
	if (p->leftchild != nullptr)
		q = p->leftchild;
	else
		q = p->rightchild;
	if (pr == nullptr)
		t = q;
	else
	{
		if (p = pr->leftchild)
			pr->leftchild = q;
		else
			pr->rightchild = q;
	}
	//����AVL����ƽ��
	while (!st.empty())
	{
		pr = st.top();
		st.pop();
		if (if(p->data < pr->data))
			pr->bf++;
		else
			pr->bf--;
		else if (pr->bf == -1 || pr->bf == 1)
			break;
		if (pr->bf != 0)
		{
			//qָ��ϸ�����
			if (pr->bf < 0)
				q = pr->leftchild;
			else
				q = pr->rightchild;
			//��һ���������
			if (q->bf == 0)
			{
				if (pr->bf < 0)
				{
					RotateR(pr);
					pr->bf = 1;
					pr->rightchild->bf = -1;
				}
				else
				{
					RotateL(pr);
					pr->bf = -1;
					pr->leftchild->bf = 1;
				}
				if (!st.empty())
				{
					AVLNode<Type> *ppr = st.top();
					if (ppr->data > pr->data)
						ppr->leftchild = q;
					else
						ppr->rightchild = q;
				}
				else
					t = pr;
				break;
			}
			//������˫��ת
			if (pr->bf < 0)
			{
				if (p->bf < 0)
				{
					RotateR(pr);
				}
				else
				{
					RotateLR(pr);
				}
			}
			else
			{
				if (p->bf > 0)
				{
					RotateL(pr);
				}
				else
				{
					RotateRL(pr);
				}
			}
			if (!st.empty())
			{
				AVLNode<Type> *ppr = st.top();
				if (ppr->data > pr->data)
					ppr->leftchild = q;
				else
					ppr->rightchild = q;
			}
			else
				t = pr;
		}
		q = pr;
	}
	delete p;
	return true;
}

//�ݻ�AVL��
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
	Destroy(t->rightchild);
	delete t;
	t = nullptr;
}

int main()
{
	AVLTree<int> avl;
	vector<int> iv = { 3, 7, 10, 5, 20, 13, 15, 19, 23, 14 };
	for (const auto &e : iv)
		avl.Insert(e);

	//cout << "Destroy begin..."<<endl;
	return 0;
}
