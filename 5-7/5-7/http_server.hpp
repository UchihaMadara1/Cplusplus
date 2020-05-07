#pragma once

#include"comm.hpp"

class httpServer
{
public:
	httpServer(int _port = 8080) :port(_port), listen_sock(-1)
	{}
	void InithttpServer()
	{
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock, port);
		Sock::Listen(listen_sock, 5);
	}
	static void* handlerRequest(void *arg)
	{
		pthread_detach(pthread_self());
		int *p = (int *)arg;
		int sock = *p;
		delete p;


		char request[10240];
		memset(request, 0, sizeof(request));

		ssize_t s = read(sock, request, sizeof(request));
		if (s > 0)
		{
			std::cout << "#########################request begin...###########################" << std::endl;
			std::cout << request << std::endl;
			std::cout << "#########################request endl...############################" << std::endl;
		}
		//response T0D0
		std::string text = "<html><h1>hello http server!!!</h1></html>";
		std::string status_line = "HTTP/1.1 200 OK\r\n";
		std::string rsp_header = "Content-Type: text/html\r\n";
		rsp_header += "Content-Length: ";
		rsp_header += std::to_string(text.size());
		rsp_header += "\r\n";
		rsp_header += "Location: www.qq.com\r\n";
		rsp_header += "Set-Cookie: name=zhangsan;sessionid=123456; path=//r/n";
		rsp_header += "\r\n";
		rsp_header += "\r\n";

		std::string response = status_line;
		response += rsp_header;
		response += text;

		write(sock, response.c_str(), response.size());
		std::cout << "#############################response begin...###########################" << std::endl;
		std::cout << response << std::endl;
		std::cout << "#############################response end...#############################" << std::endl;

		close(sock);
	}
	void Start()
	{
		for (;;)
		{
			int sock = Sock::Accept(listen_sock);
			if (sock > 0)
			{
				std::cout << "get a new link..." << std::endl;
				int *p = new int(sock);
				pthread_t tid;
				pthread_create(&tid, nullptr, handlerRequest, p);
			}
		}
	}
	~httpServer()
	{
		if (listen_sock >= 0)
		{
			close(listen_sock);
		}
	}
private:
	int listen_sock;
	int port;
};
