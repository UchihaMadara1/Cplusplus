#pragma once

#include<iostream>
#include<signal.h>
#include<string>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define BOCK_LOG 5

//工具类
class Sock
{
public:
	static int Socket()
	{
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			std::cerr << "socket error..." << std::endl;
			exit(2);
		}
		return sockfd;
	}
	static void Bind(int &sockfd, int port)
	{
		struct sockaddr_in local;
		bzero(&local, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = INADDR_ANY;
		socklen_t len = sizeof(local);
		if (bind(sockfd, (struct sockaddr*)&local, len) < 0)
		{
			std::cerr << "bind error..." << std::endl;
			exit(3);
		}
	}
	static void Listen(int sockfd, int backlog)
	{
		if (listen(sockfd, backlog) < 0)
		{
			std::cerr << "listen error..." << std::endl;
			exit(4);
		}
	}
	static int Accept(int sockfd)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int _sock = accept(sockfd, (struct sockaddr*)&peer, &len);
		if (_sock < 0)
		{
			std::cerr << "accept error..." << std::endl;
		}
		else
		{
			std::cout << "获取一个新链接..." << std::endl;
		}
		return _sock;
	}
	static void Connect(int sockfd, std::string peer_ip, int peer_port)
	{
		struct sockaddr_in peer;
		bzero(&peer, sizeof(peer));
		peer.sin_family = AF_INET;
		peer.sin_port = htons(peer_port);
		peer.sin_addr.s_addr = inet_addr(peer_ip.c_str());
		socklen_t len = sizeof(peer);
		if (connect(sockfd, (struct sockaddr*)&peer, len) < 0)
		{
			std::cerr << "connect error..." << std::endl;
			exit(3);
		}
	}
	static void Send(int sockfd, std::string &msg)
	{
		write(sockfd, msg.c_str(), msg.size());
	}
	static bool Recv(int sockfd, std::string &output)
	{
		char buf[1024];
		bool ret = true;
		ssize_t s = read(sockfd, buf, sizeof(buf)-1);
		if (s > 0)
		{
			buf[s] = 0;
			output = buf;
		}
		else if (s == 0)
		{
			std::cout << "对方关闭链接..." << std::endl;
			close(sockfd);
			ret = false;
		}
		else
		{
			std::cerr << "读取错误..." << std::endl;
			close(sockfd);
			ret = false;
		}
		return ret;
	}

};
