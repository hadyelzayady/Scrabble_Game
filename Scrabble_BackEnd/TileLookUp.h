#pragma once
#ifndef TILELOOKUP_H
#define TILELOOKUP_H
#include <iostream>
#include "Constants.h"
#include <map>
using namespace std;

class FrequencyScore 
{
public:
	
	int frequency;
	int score;

	FrequencyScore()
	{

	}
	FrequencyScore(int f, int s)
	{
		
		frequency = f;
		score = s;
	}
	~FrequencyScore()
	{

	}

	void setValues(int f, int s)
	{
		frequency = f;
		score = s;
	}

	

};


class TileLookUp
{
public:
	map<char, FrequencyScore> letterMap;

public:
	TileLookUp();
	~TileLookUp();

	void setFrequency(char c, int f);
	int  getFrequency(char c);
	int  getScore(char c);

};

#endif

