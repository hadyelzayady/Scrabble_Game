#pragma once
#include "Rack.h"
#include <string>

class Player
{

private:
	

public:

	Player(string name);		//constructor
	~Player();					//destructor

	string playerName;
	int playerScore;
	Rack *rack;

};