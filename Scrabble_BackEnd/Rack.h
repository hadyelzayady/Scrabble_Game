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
	vector <char> list;

public:


	void addTile(char x);
	void removeTile(char x);
	int getSize();

	vector<char> getRackTiles();
	vector<char> getLeave(Move move);
	vector<char> getUniqueLeave(Move move);

	// Ahmed Soliman
	inline void eraseElementFromVector(std::vector<char> &vec, int index) {
		auto it = vec.begin() + index;
		*it = std::move(vec.back());
		vec.pop_back();
	}	// Ahmed Soliman

	// Bilal
	void commitMove(Move * move);
	// Bilal

	Rack();					    //constructor
	Rack(const Rack &R);		//copy constructor
	~Rack();				    //destructor

protected:



};