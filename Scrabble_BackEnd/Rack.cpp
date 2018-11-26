#include "Rack.h"


Rack::Rack()
{
	for (int i = 0; i < Rack::RACKSIZE; i++)
	{

		list[i] = ' ';
	}
	listSize = 0;
}

Rack::Rack(const Rack & R)
{
	this->listSize = R.listSize;
	for (int i = 0; i < R.listSize; i++)
	{
		this->list[i] = R.list[i];
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