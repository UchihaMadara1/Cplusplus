#pragma once 


#include<iostream>
#include<pthread.h>
#include<string>
#include"Protocol.hpp"

class Task
{
public:
	Task()
	{}
	Task(int _sock) :sock(_sock)
	{}
	void Run()
	{
		std::cout << "Task id :" << sock << "handle thread is" << pthread_self() << std::endl;
		std::string message;
		while (true)
		{
			if (!Sock::Recv(sock, message))
			{
				std::cout << " Task break..." << std::endl;
				break;
			}
			std::cout << "ÏûÏ¢# " << message << std::endl;
			Sock::Send(sock, message);
		}
		close(sock);
	}
	~Task()
	{}
private:
	int sock;
};
