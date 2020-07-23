#pragma once

#include<iostream>
#include<unordered_map>
#include<string>
#include<sstream>

class Entry
{
public:
	static void* HandlerRequest(void *arg)
	{
		//int sock = (int)arg;
		int *p = (int*)arg;
		int sock = *p;

		//	Connect *conn = new Connect(sock);
		//	HttpRequest *rq = new HttpRequest();
		//	HttpResponse *rsp = new HttpResponse();

		//	conn->RecvHttpRequest(rq);
		//	rq->RequestLineParse();

		//Method is OK?GET  POST
		//	if(!rq->IsMethodOk())
		//	{
		LOG(Error, "request method is not ok!");
		//TODO
		//	}
		//分析url:path,paramter
		//	rq->RequestHeaderParse();
		//域名/文件资源?x=xx&&yyy=YY
		//	if(rq->IsGet())
		//	{
		//url->
		//	}
		//	else
		{

		}
		//recv request
		//parse request
		//make response
		//send response
		//	delete coon;
		//	delete rq;
		//	delete rsp;
	}
};
