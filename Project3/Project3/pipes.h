#pragma once
#include <SDKDDKVer.h>
#include<string>
#include<iostream>
#include <windows.h>
#include <atlstr.h>
#include <strsafe.h>
using namespace std;

class pipe
{
	CString PipeName;
	HANDLE hPipe;
	HANDLE hPipe2;
public:
	pipe();
	CString getPipeName();
	void sendPipe(string Message);
	string readpipe();
};