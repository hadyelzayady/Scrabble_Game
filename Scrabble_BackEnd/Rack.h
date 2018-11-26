#pragma once
#include "Square.h"
#include <iostream>
using namespace std;


class Rack
{
	enum { RACKSIZE = 7 };	//Max Size of List
private:
	char list[RACKSIZE];
	int  listSize;

public:


	void addTile(char x);
	void removeTile(char x);
	int getSize();
	void updateSize(int x);
	char* getRackTiles();

	Rack();		//constructor
	Rack(const Rack &R);		//copy constructor
	~Rack();		//destructor

protected:



};