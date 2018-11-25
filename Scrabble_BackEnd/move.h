#pragma once
#include "Play.h"
#include<vector>
class Move
{
	vector<Play>  Plays;

public:
vector<Play> getPlaysPointer()const;
void addPlay(Play play);
void  setPlayPointer(vector<Play>  Plays);
	Move();
	~Move();
};

