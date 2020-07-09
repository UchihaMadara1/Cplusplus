#pragma once

#include<iostream>
#include "Protocol.hpp"
#include "Task.hpp"
#include "Threadpool.hpp"
#include"Dict.hpp"

class Server
{
public:
	Server(std::string &_ip, int _port) :ip(_ip), port(_port), listen_sock(-1), tp(10)
	{}
	void InitServer()
	{
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock, ip, port);
		Sock::Listen(listen_sock, BACK_LOG);
		tp.InitThreadpool();
	}
	void Start()
	{
		std::cout << "###############################################" << std::endl;
		std::cout << "########请输入您要选择的服务类型：#############" << std::endl;
		std::cout << "########A.加入聊天室    B.英汉互译#############" << std::endl;
		std::cout << "###############################################" << std::endl;

		int sock = Sock::Accept(listen_sock);

		char buf[1024];

		if (sock >= 0)
		{
			ssize_t s = read(listen_sock, buf, sizeof(buf)-1);
			if (s > 0)
			{
				switch (buf[0])
				{
				case 'A':
					WeChat(sock);
					break;
				case 'B':
					WeDict(sock);
					break;
				default:
					break;
				}
			}
		}
	}
	static void* WeDictIO(void *arg)
	{
		int *p = (int*)arg;
		int sock = *p;

		delete p;

		char buf[1024];
		while (true)
		{
			ssize_t s = read(sock, buf, sizeof(buf)-1);
			if (s > 0)
			{
				buf[s] = 0;
				std::string q = buf;
				if (q == "quit" || q == "q")
				{
					std::cout << "client quit..." << std::endl;
					break;
				}
				Dict d;
				std::string value = d.Search(q);
				std::cout << "client #" << q << "->" << value << std::endl;
				write(sock, value.c_str(), value.size());
			}
			else if (s == 0)
			{
				std::cout << "client quit..." << std::endl;
				break;
			}
			else
			{
				std::cout << "client error..." << std::endl;
				break;
			}
		}
		close(sock);
		std::cout << "service done..." << std::endl;
	}
	void WeDict(int sock)
	{
		for (;;)
		{
			//int sock = Sock::Accept(listen_sock);
			if (sock >= 0)
			{
				pthread_t tid;
				int *p = new int(sock);
				pthread_create(&tid, nullptr, WeDictIO, (void*)p);
			}
		}
	}
	void WeChat(int sock)
	{
		for (;;)
		{
			std::string message;
			//int sock = Sock::Accept(listen_sock);
			if (sock >= 0)
			{
				std::cout << "get a client..." << sock << std::endl;
				Task t(sock);
				tp.PushTask(t);
			}
		}
	}
	~Server()
	{
		if (listen_sock >= 0)
		{
			close(listen_sock);
			listen_sock = -1;
		}
	}
private:
	int port;
	std::string ip;
	int listen_sock;
	Threadpool tp;
};

