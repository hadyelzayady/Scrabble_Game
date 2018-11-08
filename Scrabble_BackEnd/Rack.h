#pragma once
#include "Square.h"
#include <iostream>
using namespace std;


class Rack
{
	enum { RACKSIZE = 7 };	//Max Size of List
private:
	Square list[RACKSIZE];
	int  listSize;

public:


	void addTile(Square x);
	void removeTile(Square x);
	int getSize();
	void updateSize(int x);
	Square* getRackTiles();

	Rack();		//constructor
	~Rack();		//destructor

protected:



};