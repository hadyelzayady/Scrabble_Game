#include "Play.h"



pair<int, int> Play::get_Coordinates()
{
	return this->coordinates;
}

void Play::set_Coordinates(pair<int, int> coordinates)
{
	this->coordinates = coordinates;

}

void Play::set_Letter(char Letter)
{
	this->Letter = Letter;
}

char Play::get_Letter()
{
	return this->Letter;
}

Play::Play()
{
}


Play::~Play()
{
}
