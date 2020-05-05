#pragma once 

#include"protocol.hpp"
#include"Comm.hpp"

class server
{
public:
	server(int _port = 8080) :port(_port), listen_sock(-1)
	{}
	void Initserver()
	{
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock, port);
		Sock::Listen(listen_sock, 5);
	}
	void Service(int sock)
	{
		while (true)
		{
			Request_t rq = { 0, 0, ' ' };
			Response_t rsq = { 0, 0 };
			int s = read(sock, &rq, sizeof(rq));
			if (s > 0)
			{
				switch (rq.op)
				{
				case '+':
					rsq.result = rq.x + rq.y;
					break;
				case '-':
					rsq.result = rq.x - rq.y;
					break;
				case '*':
					rsq.result = rq.x * rq.y;
					break;
				case '/':
				{
							if (rq.y == 0)
							{
								rsq.status = -1;
							}
							else
							{
								rsq.result = rq.x / rq.y;
							}
				}
					break;
				case '%':
				{
							if (rq.y == 0)
							{
								rsq.status = -2;
							}
							else
							{
								rsq.result = rq.x % rq.y;
							}
				}
					break;
				default:
					rsq.status = -3;
					break;
				}
				write(sock, &rsq, sizeof(rsq));
			}
			else if (s == 0)
			{
				std::cout << "client quit..." << std::endl;
				break;
			}
			else
			{
				break;
			}
		}
	}
	void Start()
	{
		signal(SIGCHLD, SIG_IGN);
		for (;;)
		{
			int sock = Sock::Accept(listen_sock);
			if (sock >= 0)
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					close(listen_sock);
					Service(sock);
					exit(1);
				}
				close(sock);
			}
		}
	}
	~server()
	{
		if (listen_sock >= 0)
			close(listen_sock);
	}
private:
	int port;
	int listen_sock;
};
