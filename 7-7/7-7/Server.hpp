#pragma once

#include<iostream>
#include "Protocol.hpp"
#include "Task.hpp"
#include "Threadpool.hpp"
#include"Dict.hpp"

class Server
{
public:
	Server(std::string &_ip, int _port) :ip(_ip), port(_port), listen_sock(-1), tp(10), daily_fd(-1)
	{}
	void InitServer()
	{
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock, ip, port);
		Sock::Listen(listen_sock, BACK_LOG);
		tp.InitThreadpool();//线程池的初始化
	}
	void Start()
	{
		daily_fd = open("daily.text", O_CREAT | O_RDWR, 0664);
		if (daily_fd < 0)
		{
			std::cerr << "open error..." << std::endl;
			exit(5);
		}
		pid_t pid = fork();
		if (pid == -1)
		{
			std::cout << "fork error..." << std::endl;
			exit(6);
		}
		if (pid > 0)
		{
			while (1)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
				std::cout << "###############################################" << std::endl;
				std::cout << "########请输入您要选择的服务类型：#############" << std::endl;
				std::cout << "########1.加入会议室    2.英译汉 ##############" << std::endl;
				std::cout << "########3.汉译英        else.退出##############" << std::endl;
				std::cout << "###############################################" << std::endl;
				std::cout << "请输入服务编号 :>";
				//	int sock = Sock::Accept(listen_sock);
				//
				std::string sec = "service time is:";
				sec += GetNowTime();//调试时间
				sec += "\n";
				std::cout << sec << std::endl;
				std::string peer_ip = "peer ip is :";
				peer_ip += inet_ntoa(peer.sin_addr);
				peer_ip += "\n";
				std::cout << peer_ip << std::endl;//调试ip

				write(daily_fd, sec.c_str(), sec.size());
				write(daily_fd, peer_ip.c_str(), peer_ip.size());
				//
				char buf[1024];
				std::string service_type = "service type is:";

				if (sock >= 0)
				{
					ssize_t s = read(sock, buf, sizeof(buf)-1);
					if (s > 0)
					{
						char *s = buf;
						switch (atoi(s))
						{
						case 1:
						{
								  service_type += "聊天室";
								  service_type += "\n";
								  service_type += "------------------------";
								  service_type += "\n";
								  write(daily_fd, service_type.c_str(), service_type.size());
								  std::cout << "该用户选择了服务1，即将开始服务..." << std::endl;
								  WeChat(sock);
								  break;
						}
						case 2:
						{
								  service_type += "英译汉";
								  service_type += "\n";
								  service_type += "-----------------------";
								  service_type += "\n";
								  write(daily_fd, service_type.c_str(), service_type.size());
								  std::cout << "该用户选择了服务2，即将开始服务..." << std::endl;
								  WeDict_Etoc(sock);
								  break;
						}
						case 3:
						{
								  service_type += "汉译英";
								  service_type += "\n";
								  service_type += "-----------------------";
								  service_type += "\n";
								  write(daily_fd, service_type.c_str(), service_type.size());
								  std::cout << "该用户选择了服务3，即将开始服务..." << std::endl;
								  WeDict_Ctoe(sock);
								  break;
						}
						default:
							return;
						}
					}
				}
			}
		}
		else//日志进程
		{
			//睡眠一秒确保父进程已经完成了写操作
			sleep(1);
			char daily_rd[1024];
			lseek(daily_fd, 0, SEEK_SET);
			while (true)
			{
				int len = read(daily_fd, daily_rd, sizeof(daily_rd)-1);
			}
		}
	}
	static void* WeDictToc(void *arg)
	{
		int *p = (int*)arg;
		int sock = *p;

		delete p;

		char buf[1024];
		while (true)
		{
			ssize_t s = read(sock, buf, sizeof(buf)-1);
			if (s > 0)
			{
				buf[s] = 0;
				std::string q = buf;
				if (q == "quit" || q == "q")
				{
					std::cout << "client quit..." << std::endl;
					break;
				}
				Dict d;
				std::string value = d.Search_EtoC(q);
				std::cout << "client:" << pthread_self() << " #" << q << "->" << value << std::endl;
				write(sock, value.c_str(), value.size());
			}
			else if (s == 0)
			{
				std::cout << "client:" << pthread_self() << "quit service" << std::endl;
				break;
			}
			else
			{
				std::cout << "client:" << pthread_self() << " error..." << std::endl;
				break;
			}
		}
		close(sock);
		std::cout << "client" << pthread_self() << "service done..." << std::endl;
	}
	static void* WeDictToe(void *arg)
	{
		int *p = (int*)arg;
		int sock = *p;

		delete p;

		char buf[1024];
		while (true)
		{
			ssize_t s = read(sock, buf, sizeof(buf)-1);

			if (s > 0)
			{
				buf[s] = 0;
				std::string q = buf;
				if (q == "quit" || q == "q")
				{
					std::cout << "client quit..." << std::endl;
					break;
				}
				Dict d;
				std::string value = d.Search_CtoE(q);
				std::cout << "client:" << pthread_self() << " #" << q << "->" << value << std::endl;
				write(sock, value.c_str(), value.size());
			}
			else if (s == 0)
			{
				std::cout << "client:" << pthread_self() << "quit service" << std::endl;
				break;
			}
			else
			{
				std::cout << "client:" << pthread_self() << " error..." << std::endl;
				break;
			}
		}
		close(sock);
		std::cout << "client" << pthread_self() << "service done..." << std::endl;
	}

	void WeDict_Etoc(int sock)
	{
		//	for(;;)
		//	{
		//int sock = Sock::Accept(listen_sock);
		if (sock >= 0)
		{
			pthread_t tid;
			int *p = new int(sock);
			pthread_create(&tid, nullptr, WeDictToc, (void*)p);
		}
		//	}
	}
	void WeDict_Ctoe(int sock)
	{
		if (sock >= 0)
		{
			pthread_t tid;
			int *p = new int(sock);
			pthread_create(&tid, nullptr, WeDictToe, (void*)p);
		}
	}
	void WeChat(int sock)
	{
		//	for(;;)
		//	{
		std::string message;
		//		int sock = Sock::Accept(listen_sock);
		if (sock >= 0)
		{
			std::cout << "get a client..." << sock << std::endl;
			Task t(sock);
			tp.PushTask(t);
		}
		//	}
	}
	~Server()
	{
		if (listen_sock >= 0)
		{
			close(listen_sock);
			listen_sock = -1;
		}
		if (daily_fd >= 0)
		{
			close(daily_fd);
			daily_fd = -1;
		}
	}
public:
	static std::string GetNowTime()//返回当前时间
	{
		timespec time;
		clock_gettime(CLOCK_REALTIME, &time);//获取时间戳
		tm nowTime;
		localtime_r(&time.tv_sec, &nowTime);
		char current[1024];
		sprintf(current, "%04d.%02d.%02d,%02d:%02d:%2d", nowTime.tm_year + 1900, nowTime.tm_mon + 1, nowTime.tm_mday, nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
		return current;
	}
private:
	int port;
	std::string ip;
	int listen_sock;
	Threadpool tp;
	int daily_fd;
};
