#include "Play.h"



pair<int, int> Play::get_Cooridantes()
{
	return this->cooridantes;
}

void Play::set_Cooridantes(pair<int, int> Corridantes)
{
	this->cooridantes = Corridantes;

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
