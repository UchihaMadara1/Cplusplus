#pragma once

#include<iostream>
#include<string>
#include<sys/time.h>

//normal error
#define ARG_ERR 1
#define SOCKET_CREATE 2
#define BIND_ERROR 3
#define LISTEN_ERROR 4

//log error level
#define Normal 1
#define Warning 2
#define Error 3
#define Fatal 4

//back log
#define NUM 5


uint64_t GetTimeStamp()
{
	struct timeval _time;
	if (gettimeofday(&_time, nullptr) == 0)
	{
		return _time.tv_sec;
	}
	return 0;
}

//���󼶱�  ������Ϣ  ����ʱ�� ģ������  ��ӡ�к�
void Log(std::string level, std::string msg, std::string model, int number)
{
	std::cout << "[" << level << "][" << msg << "][" << GetTimeStamp() << "][" << model << "][" << number << "]" << std::endl;
}

#define LOG(ERR_LEVEL,MESSAGE)\
	Log(#ERR_LEVEL, MESSAGE, __FILE__, __LINE__)
