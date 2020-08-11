#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

class solution
{
public:
	static void print()
	{
		cout << m_data << endl;
	}
	bool IsTrue()
	{
		return m_data;
	}
private:
	static int m_data;
};

int solution::m_data = -1;

int main()
{
	solution *s = nullptr;
	if (s->IsTrue())
		s->print();
	return 0;
}