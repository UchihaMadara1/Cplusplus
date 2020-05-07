#define _CRT_SECURE_NO_WARNINGS

#include "http_server.hpp"


void Usage(std::string proc)
{
	std::cout << "Usage:" << proc << " " << "port" << std::endl;
}
//server  port
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		Usage(argv[0]);
		exit(0);
	}
	httpServer *sp = new httpServer(atoi(argv[1]));
	sp->InithttpServer();
	sp->Start();
	delete sp;
	return 0;
}

