#pragma once
#include "Square.h"
#include<vector>
#include "Rack.h"
#include "move.h"
#include <iostream>
using namespace std;


class Rack
{
	enum { RACKSIZE = 7 };	//Max Size of List
private:
	vector <char> list;

public:


	void addTile(char x);
	void removeTile(char x);
	int getSize();

	vector<char> getRackTiles();
	vector<char> getLeave(Move move, Rack current)

	Rack();					    //constructor
	Rack(const Rack &R);		//copy constructor
	~Rack();				    //destructor

protected:



};