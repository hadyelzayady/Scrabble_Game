#pragma once
#include <stdio.h>
#include "easywsclient.h"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <string>
#include "Enums.h"
#include "structs.h"
#include <string>
#include <iostream>
using easywsclient::WebSocket;
using namespace std;
class Client
{
private:
	States state;
	
	vector<uint8_t> encodeInitState(string name);
	vector<uint8_t> encodeTiles(vector<string>v);
	
public:
	Client();
	void setState(States s);
	States getState();

	
	void sendInitState(unique_ptr<WebSocket> &ws,string name);
	void sendPass(unique_ptr<WebSocket> &ws);
	void sendExchange(unique_ptr<WebSocket> &ws,vector<string> tiles);
	readyStruct_formated decodeReadyState(std::vector<uint8_t>& message);
	~Client();
};

