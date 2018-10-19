#pragma once
#ifndef TILELOOKUP_H
#define TILELOOKUP_H
#include <string>
#include <iostream>
using namespace std;

class Letter
{
public:
	
	string letter;
	int frequency;
	int score;
	Letter(string l, int f, int s)
	{
		letter = l;
		frequency = f;
		score = s;
	}
	~Letter()
	{

	}

};


class TileLookUp
{
public:
	Letter * letterArray[27];

public:
	TileLookUp();
	~TileLookUp();

};

#endif

