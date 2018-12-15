#include "move.h"
vector<Play> Move::getPlaysPointer()const
{

	return this->Plays;

}

void Move::addPlay(Play play)
{
	this->Plays.push_back(play);
	this->chars.push_back(play.Letter);
	

}

void Move::addPlay(int x ,int y ,char l,bool blank)
{
	Play play(x, y, l,blank);
	this->Plays.push_back(play);
	this->chars.push_back(play.Letter);
}

void Move::setPlayPointer(vector<Play> Plays)
{
	this->Plays = Plays;
}

Move::Move()
{
	
}

Move::Move(const Move& other)
{
	for (int i = 0; i < other.Plays.size(); i++)
			this->Plays.push_back(other.Plays[i]);
	this->chars = other.chars;
	isBingo = other.isBingo;
	score = other.score;
}

void Move::setBingo(bool bingo) {
	isBingo = bingo;
}
bool Move::getBingo() {
	return isBingo;
}


Move::~Move()
{
	
}
