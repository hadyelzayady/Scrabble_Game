#pragma once
#ifndef TILELOOKUP_H
#define TILELOOKUP_H
#include <iostream>
#include "Constants.h"
#include <map>
using namespace std;


class TileLookUp
{
public:
	map<char, int*> letterMap;

public:
	TileLookUp();
	~TileLookUp();

	void setFrequency(char c, int f);
	int  getFrequency(char c);
	int  getScore(char c);

};

#endif

