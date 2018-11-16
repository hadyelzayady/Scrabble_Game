#include "ProbabilityManager.h"



double ProbabilityManager::hyperGeometricDistrubution(int population, int cluster, int specialElementsCount, int specialElementsDesired)
{
	return	(double)((double)myUtilities.C(specialElementsCount, specialElementsDesired) * 
			(double)myUtilities.C(population - specialElementsCount, cluster - specialElementsDesired) /
			(double)myUtilities.C(population, cluster));
}

double ProbabilityManager::calculateRackWeight(char * opponentRack, vector<pair<char, int>> availableFrequencies)
{
	double returnValue = 1;
	int population = 0;
	for (int i = 0; i < availableFrequencies.size(); i++) {
		population += availableFrequencies[i].second;
	}

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < availableFrequencies.size(); j++) {
			if (availableFrequencies[j].first == opponentRack[i]) {
				returnValue *= hyperGeometricDistrubution(population - i, RACK_SIZE - i, availableFrequencies[j].second, 1);
				availableFrequencies[j].second--;
			}
		}
	}
	return returnValue;
}

ProbabilityManager::ProbabilityManager(TileLookUp* t)
{
	tileLookup = t;
}


ProbabilityManager::~ProbabilityManager()
{
}
