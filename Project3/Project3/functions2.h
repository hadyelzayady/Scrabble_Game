#pragma once
#include"structs.h"
#include<vector>
#include<string>
using namespace std;
playerStart parseStart(std::string Message)
{
	playerStart Start;
	std::string delimiter = ",";
	vector<string>v;

	size_t pos = 0;
	std::string token;
	while ((pos = Message.find(delimiter)) != std::string::npos) {
		token = Message.substr(0, pos);
		v.push_back(token);
		Message.erase(0, pos + delimiter.length());
	}
	Start.PlayerName = v[0];
	Start.connection = "ws://";
	Start.connection += v[1];
	//Start.mode = v[2];
	return Start;
}
