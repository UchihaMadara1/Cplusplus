#pragma once

#include<iostream>
#include "Protocol.hpp"

class Client
{
public:
	Client(std::string &_ip, int _port) :ip(_ip), port(_port), sock(-1)
	{}
	void InitClient()
	{
		sock = Sock::Socket();
		Sock::Connect(sock, ip, port);
	}
	void Start()
	{
		std::string input;
		std::cout << "####################################################" << std::endl;
		std::cout << "##################请选择服务类型####################" << std::endl;
		std::cout << "#############1.加入聊天室  2.英译汉服务#############" << std::endl;
		std::cout << "#############3.汉译英服务  0.退出      #############" << std::endl;
		std::cout << "####################################################" << std::endl;
		std::cout << "请选择服务类型#";
		std::cin >> input;
		Sock::Send(sock, input);
		while (true)
		{
			//std::string input;
			std::string output;
			std::cout << "请输入#";
			std::cin >> input;
			//	getline(std::cin,input);
			Sock::Send(sock, input);

			if (Sock::Recv(sock, output))
			{
				std::cout << "服务器回显#" << output << std::endl;
			}
			else
			{
				break;
			}
		}
	}
	~Client()
	{
		if (sock >= 0)
		{
			close(sock);
			sock = -1;
		}
	}
private:
	std::string ip;
	int port;
	int sock;
};
