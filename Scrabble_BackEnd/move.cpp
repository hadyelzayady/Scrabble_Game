#include "move.h"
vector<Play> Move::getPlaysPointer()
{

	return this->Plays;

}

void Move::addPlay(Play play)
{
	this->Plays.push_back(play);
	

}

void Move::setPlayPointer(vector<Play> Plays)
{
	this->Plays = Plays;
}

Move::Move()
{

}


Move::~Move()
{

}
