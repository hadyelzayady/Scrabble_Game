#pragma once
#include "Rack.h"


class Player
{

private:
	string playerName;
	int playerScore;
	Rack *rack;



public:

	Player(string name);		//constructor
	~Player();					//destructor

	string getPlayerName();
	int getPlayerScore();
	void editPlayerScore(int score);
	Rack &getRack();
protected:



};