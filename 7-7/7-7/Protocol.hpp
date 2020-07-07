#pragma once

#include<iostream>
#include<string>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<stdio.h>
#include<time.h>

#define BACK_LOG 5

//工具类
class Sock
{
public:
	static int Socket()//申请套接字,套接字就是IP地址+端口号，IP地址是用来定位公网内唯一的一台主机，而端口号则用来定位一台主机内的唯一的一个进程
	{
		int sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
		{
			std::cerr << "socket error..." << std::endl;
			exit(2);
		}
		return sockfd;
	}
	static void Bind(int &sockfd, std::string ip, int port)//绑定端口号
	{
		struct sockaddr_in local;
		bzero(&local, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = inet_addr(ip.c_str());

		socklen_t len = sizeof(local);

		int opt = 1;
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

		if (bind(sockfd, (struct sockaddr*)&local, len) < 0)
		{
			std::cerr << "bind error..." << std::endl;
			exit(3);
		}
	}
	static void Listen(int sockfd, int backlog)//监听
	{
		if (listen(sockfd, backlog) < 0)
		{
			std::cerr << "listen error..." << std::endl;
			exit(4);
		}
	}
	static int Accept(int sockfd)//获取连接
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
	static void Connect(int sockfd, std::string peer_ip, int peer_port)//链接服务器
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
	static void Send(int sockfd, std::string &msg)//用于双工通信发送信息
	{
		write(sockfd, msg.c_str(), msg.size());
	}
	static bool Recv(int sockfd, std::string &output)//双工通信接收消息
	{
		char buf[10240];
		bool ret = true;
		ssize_t s = read(sockfd, buf, sizeof(buf)-1);
		if (s > 0)
		{
			buf[s] = 0;
			output = buf;
		}
		else if (s == 0)
		{
			std::cout << pthread_self() << "关闭链接..." << std::endl;
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
