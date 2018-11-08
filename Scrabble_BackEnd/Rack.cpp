#include "Rack.h"


Rack::Rack()
{
	for (int i = 0; i < Rack::RACKSIZE; i++)
	{
		list[i].points = 0;
		list[i].letter = ' ';
	}
	listSize = 0;
}


void Rack::addTile(Square x)
{
	if (listSize == 7)
		return;

	list[listSize] = x;
	listSize++;
}

Square* Rack::getRackTiles()
{
	return list;
}

void Rack::removeTile(Square x)
{

	for (int i = 0; i < listSize; i++)
	{
		if (list[i].letter == x.letter)
		{
			for (int j = i; j < (listSize - i - 1); i++)
			{
				list[j] = list[j + 1];

			}

			break;
		}
	}
	list[listSize].points = 0;
	list[listSize].letter = ' ';
	listSize--;

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