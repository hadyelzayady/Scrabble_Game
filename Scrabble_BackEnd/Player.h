#pragma once
#include "Rack.h"
#include <string>

class Player
{
public:
	string playerName;
	int playerScore;
	Rack *rack;
	Player(string name);		//constructor
	~Player();					//destructor
};