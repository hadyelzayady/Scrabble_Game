#pragma once
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

	Rack();		//constructor
	~Rack();		//destructor

protected:



};