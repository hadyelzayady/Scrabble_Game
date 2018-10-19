#pragma once
#ifndef TILELOOKUP_H
#define TILELOOKUP_H
#include <string>
#include <iostream>
#include "Constants.h"
using namespace std;

class Letter
{
public:
	
	char letter;
	int frequency;
	int score;
	Letter(char l, int f, int s)
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

