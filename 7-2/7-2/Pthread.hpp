#pragma once

#include"Task.hpp"
#include"Protocol.hpp"
#include<queue>

class Threadpool
{
public:
	Threadpool(int _sum = 5) :sum(_sum)
	{
		pthread_mutex_init(&mutex, nullptr);
		pthread_cond_init(&cond, nullptr);
	}
	bool IsEmpty()//��������п�
	{
		return q.empty();
	}
	void LockQueue()//����
	{
		pthread_mutex_lock(&mutex);
	}
	void UnlockQueue()//����
	{
		pthread_mutex_unlock(&mutex);
	}
	void ThreadWait()//�ź�������
	{
		std::cout << "thread: " << pthread_self() << " wait..." << std::endl;
		pthread_cond_wait(&cond, &mutex);
	}
	void Wakeup()//���������
	{
		std::cout << "thread: " << pthread_self() << " wakeup,handler task..." << std::endl;
		pthread_cond_signal(&cond);
	}
	void PopTask(Task &t)//�����������ȡ��һ������
	{
		t = q.front();
		q.pop();
	}
	void PushTask(Task &t)//�����������������
	{
		LockQueue();
		q.push(t);
		UnlockQueue();
		Wakeup();
	}
	static void* HandlerTask(void *arg)//���߳�ִ����
	{
		pthread_detach(pthread_self());
		Threadpool *tp = (Threadpool*)arg;
		for (;;)
		{
			Task t;
			tp->LockQueue();
			while (tp->IsEmpty())
			{
				tp->ThreadWait();
			}
			tp->PopTask(t);
			tp->UnlockQueue();
			t.Run();
		}
	}
	void InitThreadpool()//�̳߳س�ʼ��
	{
		for (int i = 0; i < sum; ++i)
		{
			pthread_t tid;
			pthread_create(&tid, nullptr, HandlerTask, (void*)this);
		}
	}
	~Threadpool()
	{
		pthread_mutex_destroy(&mutex);
		pthread_cond_destroy(&cond);
	}
private:
	size_t sum;
	std::queue<Task> q;
	pthread_cond_t cond;
	pthread_mutex_t mutex;
};
