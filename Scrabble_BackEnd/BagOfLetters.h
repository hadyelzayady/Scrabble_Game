#pragma once
#include <stdio.h>
#include <string.h>
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <random>
class BagOfLetters {

	int bag[27];	//Stack used to represent the letter bag
	int size;
public:
	//Constructor
	BagOfLetters();

	char draw();
	//Swap tiles
	char swap(char b);

	int getSize();

	bool hasLetters();

	//void fillRack(Rack* r);
};
