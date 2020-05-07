#define _CRT_SECURE_NO_WARNINGS
http_server : http_server.cpp
	g++ - o $@ $^ -lpthread - std = c++11
	.PHONY:clean
clean :
			  rm - f http_server
