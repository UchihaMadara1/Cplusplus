#define _CRT_SECURE_NO_WARNINGS
cc = g++

.PHONY:all
all : server client

  server : server.cpp
		   $(cc) - o $@ $^ -std = c++11 - lpthread
	   client : client.cpp
				$(cc) - o $@ $^ -std = c++11 - lpthread
				.PHONY:clean
			clean :
rm - f server client

