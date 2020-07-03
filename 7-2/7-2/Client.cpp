#define _CRT_SECURE_NO_WARNINGS

#include "Client.hpp"
#include<iostream>



void Usage(std::string proc)
{
	std::cout << proc << " " << "ip port" << std::endl;
}
int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}
	std::string ip = argv[1];
	int port = atoi(argv[2]);

	Client *cp = new Client(ip, port);

	cp->InitClient();
	cp->Start();

	return 0;
}

