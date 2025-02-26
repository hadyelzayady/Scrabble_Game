#pragma once
#include "Square.h"
#include<vector>
#include "Rack.h"
#include "move.h"
#include <map>
#include <iostream>
using namespace std;


class Rack
{
	enum { RACKSIZE = 7 };	//Max Size of List
private:
	

public:

	vector <char> list;
	void addTile(char x);
	void removeTile(char x);
	int getSize();

	vector<char> getRackTiles();
	vector<char> getLeave(Move move);
	vector<char> getUniqueLeave(Move move);
	void removeMoveTiles(const Move & move);
	Rack();					    //constructor
	Rack(const Rack &R);		//copy constructor
	~Rack();				    //destructor

protected:



};