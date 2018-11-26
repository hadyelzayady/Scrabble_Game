#include "Rack.h"


Rack::Rack()
{
	for (int i = 0; i < Rack::RACKSIZE; i++)
	{
		
		list[i] = ' ';
	}
	listSize = 0;
}


void Rack::removeMoveTiles(const Move & move)
{
	vector<Play> plays = move.getPlaysPointer();
	for (size_t i = 0; i <plays.size; i++)
	{
		removeTile(plays[i].get_Letter());
	}
}

void Rack::addTile(char x)
{
	if (listSize == 7)
		return;

	list[listSize] = x;
	listSize++;
}

char* Rack::getRackTiles()
{
	return list;
}

void Rack::removeTile(char x)
{

	for (int i = 0; i < listSize; i++)
	{
		if (list[i] == x)
		{
			list[i] = list[listSize];
			list[listSize] = ' ';
			listSize--;
			break;
		}
	}

}



int Rack::getSize()
{
	return listSize;
}

void Rack::updateSize(int x)
{
	listSize = x;
}


Rack::~Rack()
{


}