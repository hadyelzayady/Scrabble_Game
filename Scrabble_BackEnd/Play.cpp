#include "Play.h"



pair<int, int> Play::get_Coordinates()
{
	return this->coordinates;
}

void Play::set_Coordinates(pair<int, int> coordinates)
{
	this->coordinates = coordinates;

}

void Play::set_Letter(char Letter,int index,bool blank= false)
{
	this->Index = index; 
	this->Blank =  blank;
	this->Letter = Letter;
}

int Play::get_Index(int index){
	return this->Index;
}

bool Play::isBlank(){
	return this->Blank;
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
