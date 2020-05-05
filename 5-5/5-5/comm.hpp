#pragma once

#include<iostream>
#include<string>

//x op y =
typedef struct Request
{
	int x;
	int y;
	char op;
}Request_t;

typedef struct REsponse
{
	int status;
	int result;
}Response_t;
