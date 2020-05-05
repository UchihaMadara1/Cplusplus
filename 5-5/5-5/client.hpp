#pragma once 

#include"protocol.hpp"
#include"Comm.hpp"

class client
{
public:
	client(std::string ip = "127.0.0.1", int port = 8080) :server_ip(ip), server_port(port), sock(-1)
	{}
	void Initclient()
	{
		sock = Sock::Socket();
	}
	void Start()
	{
		Sock::Connect(sock, server_ip, server_port);
		for (;;)
		{
			Request_t rq;
			Response_t rsp;
			std::cout << "Enter your data<x,y>#";
			std::cin >> rq.x >> rq.y;
			std::cout << "Enter your op<+-*/%>#";
			std::cin >> rq.op;

			write(sock, &rq, sizeof(rq));
			ssize_t s = read(sock, &rsp, sizeof(rsp));
			if (s > 0)
			{
				std::cout << "status#" << rsp.status << std::endl;
				std::cout << "result#" << rq.x << rq.op << rq.y << "=" << rsp.result << std::endl;
				std::cout << "-------------------------------------------------" << std::endl;
			}
			else
				break;
		}
		close(sock);
		sock = -1;
	}
	~client()
	{
		if (sock >= 0)
			close(sock);
	}
private:
	int server_port;
	std::string server_ip;
	int sock;
};
