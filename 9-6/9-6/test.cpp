#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;
//
//struct Father
//{
//	friend ostream &operator<<(ostream &out,Father &fa);
//	virtual ostream& operator<<(ostream &out)
//	{
//		out << "Father";
//		return out;
//	}
//	void run()
//	{
//		this->fun();
//	}
//	virtual void fun()
//	{
//		cout << "this is father..." << endl;
//	}
//private:
//	int a;
//};
//
//struct Son:public Father
//{
//	virtual ostream& operator<<(ostream &out)
//	{
//		out << "Son";
//		return out;
//	}
//	virtual void fun()
//	{
//		cout << "this is son..." << endl;
//	}
//	void run()
//	{
//		this->fun();
//	}
//private:
//	int x;
//};
//
//ostream& operator<<(ostream &out,Father &fa)
//{
//	out << "Father";
//	return out;
//}
//int main()
//{
//	Son son;
//	Father fa;
//	Father &ptr = son;
//	/*cout << son << endl;
//	*ptr<< cout;*/
//	fa.run();
//	son.run();
//	ptr.run();
//	//(*ptr).run();
//	return 0;
//}

//template<class T1,typename T2>
//class pair
//{
//	typedef T1 first_type;
//	typedef T2 second_type;
//
//	T1 first;
//	T2 second;
//
//	pair() :first(T1())
//	{}
//	pair(const T1 &a, const T2 &b) :first(a), second(b)
//	{}
//};
//
//int main()
//{
//	int arr[] = {1,2,3,2,3,3,3,3,3,4,5,6,7,8,9,0};
//	int a = 5;
//	set<int> s(arr, arr + sizeof(arr) / sizeof(arr[0]));
//	set<int> st(s);
//	set<int> all;
//	if ((st.insert(10)).second)
//		cout << "true" << endl;
//	cout << st.size() << endl;
//	s.erase(s.begin(),s.end());
//	for (auto &e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	while (a < 20)
//	{
//		s.insert(++a);
//	}
//	s.swap(st);
//	for (auto &e : s)
//	{
//		cout << e << " ";
//	}
//	cout << endl;
//	for (auto &e : st)
//	{
//		cout << e<<" ";
//	}
//	cout << endl;
//	cout << s.count(3) << endl;
//	cout << (*s.find(3)) << endl;
//
//	//set_union(s.begin(),s.end(),st.begin(),st.end(),inserter(all,all.begin()));
//	//set_union(s.begin(), s.end(), st.begin(), st.end(), ostream_iterator(cout," "));
//	//set_intersection(s.begin(),s.end(),st.begin(),st.end(),inserter(all,all.begin()));
//	//set_difference(s.begin(), s.end(), st.begin(), st.end(), inserter(all, all.begin()));
//	//set_symmetric_difference(s.begin(), s.end(), st.begin(), st.end(), inserter(all, all.begin()));
//	for (auto &e : all)
//	{
//		cout << e<<" ";
//	}
//	cout << endl;
//	return 0;
//}
//
