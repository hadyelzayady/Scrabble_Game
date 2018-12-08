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
	// vector<Play> plays = move.Plays;
	vector<char> leave = this->list;

	int size = move.Plays.size();

	for (int i = 0; i < size; i++) {
		leave.erase(std::remove(leave.begin(), leave.end(), move.Plays[i].Letter), leave.end());
		//this->eraseElementFromVector(leave, move.Plays[i].Letter);
	}
	return leave;
}

void Rack::commitMove(Move * move)
{
	int size = move->Plays.size();
	for (int i = 0; i < size; i++) {
		this->list.erase(std::remove(this->list.begin(), this->list.end(), move->Plays[i].Letter), this->list.end()); // eraseElementFromVector now uses index not value so USED STD::REMOVE instead
		//this->eraseElementFromVector(this->list, move->Plays[i].Letter);
	}
}



// TODO: Optimise to use eraseElementFromVector functon
vector<char> Rack::getUniqueLeave(Move move)
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


	for (int i = 0; i < leave.size(); i++)
	{
		for (int k = i + 1; k < leave.size(); k++)
		{
			if (leave[i] == leave[k])
				leave.erase(leave.begin() + k);
		}

	}

	return leave;

}


void Rack::addTile(char x)
{
	if (list.size() == 7)
		return;

	list.push_back(x);

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