#pragma once

#include<iostream>
#include<string>
#include<strings.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<sys/socket.h>

using namespace std;

class Sock
{
public:
	static int Socket()
	{

	}
	void static Bind(int listen_sock, int port)
	{

	}
	void static Listen(int listen_sock)
	{

	}
	void static Accept()
	{

	}
};

class epoll_Server
{
public:
	epoll_Server() :port(8080), listen_sock(-1), epfd(-1)
	{}
	epoll_Server(int _port) :port(_port), listen_sock(-1), epfd(-1)
	{}
	~epoll_Server()
	{
		if (listen_sock >= 0)
			close(listen_sock);
		if (epfd >= 0)
			close(epfd);
	}
public:
	void Init_epoll()
	{
		epfd = epoll_create(128);
		if (epfd < 0)
		{
			cerr << "epoll_create error...." << endl;
			exit(2);
		}

		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock, port);
		Sock::Listen(listen_sock);
	}
	void Handlerevent(struct epoll_event rcvs[], int num)
	{
		for (int i = 0; i < num; ++i)
		{
			if (rcvs[i].events & EPOLLIN)
			{
				if (rcvs[i].data.fd == listen_sock)
				{
					//读取链接
				}
				else
				{
					//读取日常数据
				}
			}
			else if (rcvs[i].events & EPOLLOUT)
			{
				//处理写事件
			}
			else
			{
				//异常事件
			}
		}
	}
	void Start()
	{
		struct epoll_event ev;
		ev.events = EPOLLIN;
		ev.data.fd = listen_sock;
		epoll_ctl(epfd, EPOLL_CTL_ADD, listen_sock, &ev);

		struct epoll_event rcvs[128];
		for (;;)
		{
			int num = 0;
			int timeout;
			switch (epoll_wait(epfd, rcvs, 128, timeout))
			{
			case -1:
				cerr << "epoll_wait..." << endl;
				break;
			case 0:
				cout << "time out..." << endl;
				break;
			default:
				//success
				Handlerevent(rcvs, num);
				break;
			}
		}
	}
private:
	int port;
	int listen_sock;
	int epfd;
};

