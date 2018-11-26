#include "Rack.h"


Rack::Rack()
{
	list.reserve(7);

}

Rack::Rack(const Rack & R)
{
		this->list.reserve(7);
	
		this->list = R.list;
	

}

vector<char> Rack::getLeave(Move move) 
{
	vector<Play> plays = move.getPlaysPointer();
	vector<char> leave = this->list;

	for (int i = 0; i < plays.size(); i++)
	{
		for (int k = 0; k < leave.size(); k++)
		{
			if (leave[k] == plays[i].get_Letter())
				leave.erase(leave.begin() + k);
		}

	}
	return leave;
}


void Rack::addTile(char x)
{
	if (list.size() == 7)
		return;

	list[list.size()] = x;

}

vector<char> Rack::getRackTiles()
{
	return list;
}

void Rack::removeTile(char x)
{

	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] == x)
		{
			
			list.erase(list.begin() + i);

			break;
		}
	}

}



int Rack::getSize()
{
	return list.size();
}



Rack::~Rack()
{


}