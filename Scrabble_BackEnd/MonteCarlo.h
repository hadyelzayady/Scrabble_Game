#pragma once
#include "TileLookUp.h"
#include "Rack.h"
#include "ProbabilityManager.h"
#include <random>
class MonteCarlo
{
	TileLookUp * tileLookUp;
	char *  myrackchars; 
	char * boardPool;
	ProbabilityManager * Pm;
	std::vector<char> availableCharacters;
	std::vector<pair<char, int>> availableFrequinces;
public:
	MonteCarlo( Rack * myRack , char * boardPool, ProbabilityManager *pm);
	void createAvaliableLetters();
	void simulation(int N = 100);
	~MonteCarlo();
};

