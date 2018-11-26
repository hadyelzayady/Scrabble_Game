#include "move.h"
vector<Play> Move::getPlaysPointer()const
{

	return this->Plays;

}

void Move::addPlay(Play play)
{
	this->Plays.push_back(play);
	

}

void Move::addPlay(int x ,int y ,char l,bool blank)
{
	Play play(x, y, l,blank);
	this->Plays.push_back(play);


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
	Plays = other.Plays;
	isBingo = other.isBingo;
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
