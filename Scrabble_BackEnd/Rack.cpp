#include "Rack.h"


Rack::Rack()
{
	//for (int i = 0; i < Rack::RACKSIZE; i++)
	//	list[i] = ' ';
	listSize = 0;

}


void Rack::addTile(char x)
{
	if (listSize == 7)
		return;

	list[listSize] = x;
	listSize++;
}

void Rack::removeTile(char x)
{

	for (int i = 0; i < listSize; i++)
	{
		if (list[i] == x)
		{
			for (int j = i; j < (listSize - i - 1); i++)
			{
				list[j] = list[j + 1];

			}

			break;
		}
	}
	list[listSize] = ' ';
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