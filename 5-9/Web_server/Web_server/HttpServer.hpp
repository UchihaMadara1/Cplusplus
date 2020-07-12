#pragma once

#include<iostream>
#include"Log.hpp"
#include"Protocol.hpp"
#include"Sock.hpp"
#include<pthread.h>

#define DefaultPort 8081

using namespace std;

class HttpServer
{
public:
	HttpServer(int _port) :port(_port), listen_sock(-1)
	{}
	HttpServer() :listen_sock(-1)
	{}
	~HttpServer()
	{
		if (listen_sock >= 0)
			close(listen_sock);
	}
public:
	void InitServer()
	{
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock, port);
		Sock::Listen(listen_sock);
	}
	void Start()
	{
		LOG(Normal, "Start server success...");
		for (;;)
		{
			int sock = Sock::Accept(listen_sock);
			if (sock >= 0)
			{
				LOG(Normal, "get a new link...");
				pthread_t tid;
				pthread_create(&tid, nullptr, Entry::HandlerRequest, (void*)&sock);//need fix
				pthread_detach(tid);
			}
		}
	}
private:
	int port;
	int listen_sock;
};
