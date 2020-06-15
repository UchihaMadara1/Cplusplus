#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <strings.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#define MAX sizeof(fd_set)*8

using namespace std;


class selectServer{
private:
	int port;
	int listen_sock;
	vector<int> vfds;
public:
	selectServer() :port(8080), listen_sock(-1), vfds(MAX, -1){}
	selectServer(int _port) :port(_port), listen_sock(-1), vfds(MAX, -1){}

	void initServer()
	{
		struct sockaddr_in local;
		bzero(&local, sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = htonl(INADDR_ANY);

		listen_sock = socket(AF_INET, SOCK_STREAM, 0);
		if (listen_sock < 0){
			cerr << "socket error" << endl;
			exit(2);
		}
		if (bind(listen_sock, (struct sockaddr*)&local, sizeof(local)) < 0){
			cerr << "bind error" << endl;
			exit(3);
		}
		if (listen(listen_sock, 5) < 0){
			cerr << "listen error" << endl;
			exit(4);
		}
		int opt = 1;
		setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	}
	void handlerEvents(fd_set *rfds) //����ʱ��rfds���������os->user��Щ�ļ�����������Ķ��¼��Ѿ�������
	{
		//1111 1111
		//0110 1000
		for (int i = 0; i < MAX; i++){ //ѭ�������Ӧ������ʱ��
			if (vfds[i] < 0){
				continue;
			}
			if (FD_ISSET(vfds[i], rfds)){ //˵����ǰ�ļ�����������Ķ��¼��Ѿ�������
				if (vfds[i] == listen_sock){
					//1. ��ȡ����
					struct sockaddr_in peer;
					socklen_t len = sizeof(peer);
					int sock = accept(listen_sock, (struct sockaddr*)&peer, &len);
					if (sock < 0){
						cerr << "accept error" << endl;
						continue;
					}
					cout << "get a new link... : " << sock << endl;
					//a. ��ȡ���� b. ��sock�йܸ�select(��ȷ��)
					//�����һ����Ч���ӣ�����������һ����������?
					//read, read�ͻ�����
					//������û�о�����ֻ��select�����
					int j = 0;
					for (; j < MAX; j++){
						if (vfds[j] == -1){
							break;
						}
					}
					if (j == MAX){
						cout << "server full" << endl;
						close(sock);
					}
					else{
						vfds[j] = sock; //��̬����µ�sock��ȫ�����鵱�У��Ա�����´���select�����ǽ��о���ʱ����
					}
				}
				else{
					//2. ��ȡ����
					char buffer[10240];
					ssize_t s = recv(vfds[i], buffer, sizeof(buffer)-1, 0);
					if (s > 0){
						buffer[s] = 0;
						cout << "client# " << buffer << endl;
					}
					else{ //s < 0 or s == 0
						if (s == 0){
							cout << "peer link close, server close too!" << endl;
						}
						else{
							cout << "recv error!, server close!" << endl;
						}
						close(vfds[i]);
						vfds[i] = -1; //��취�Ƴ��ϵ�sock���Է�select��������
					}//else
				}//
			}
			else{
				//˵����ǰ�ļ�����������Ķ��¼���û�о�����
				cout << vfds[i] << " : curr fd is not ready!" << endl;
			}
		}
	}
	void start()
	{
		vfds[0] = listen_sock;
		fd_set rfds;

		for (;;){
			//struct timeval timeout = {0, 0};
			int maxfd = listen_sock;
			FD_ZERO(&rfds);
			for (auto it = vfds.begin(); it != vfds.end(); it++){ //ѭ�����
				if (*it < 0){
					continue;
				}
				FD_SET(*it, &rfds);
				if (maxfd < *it){
					maxfd = *it;
				}
			}
			cout << "maxfd: " << maxfd << endl;
			//�����ٶ�һ��һ�����飬������鱣��������е�д�ļ�������
			//���õ�ʱ�򣬴������user->os��Щ�ļ�����������Ķ��¼��㣨os��Ҫ���ҹ���
			switch (select(maxfd + 1, &rfds, nullptr, nullptr, /*&timeout*/nullptr)){ //�ļ�������select�ȴ�
			case 0:
				cout << "time out ..." << endl;
				break;
			case -1:
				cerr << "select error!" << endl;
				break;
			default:
				cout << "get a event" << endl;
				//success
				handlerEvents(&rfds); //����ʱ��rfds���������os->user��Щ�ļ�����������Ķ��¼��Ѿ�������
				break;
			}
		}
	}
};





