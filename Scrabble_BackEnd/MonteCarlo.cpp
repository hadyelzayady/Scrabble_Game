#include "MonteCarlo.h"




MonteCarlo::MonteCarlo( Rack * myRack, char * boardPool, ProbabilityManager *pm)
{
	this->Pm = pm;
	this->myrackchars = myRack->getRackTiles();
	this->boardPool = boardPool;
}


void MonteCarlo::createAvaliableLetters()
{

	this->tileLookUp = new TileLookUp();
	int size = sizeof(mapping) / sizeof(char);
		for(int i = 0; i < size-1; i++)
		{
			char * a = strchr(this->myrackchars,mapping[i]);
			char * b = strchr(this->boardPool, mapping[i]);
			if (a != NULL)
				this->tileLookUp->setFrequency(mapping[i], this->tileLookUp->getFrequency(mapping[i]) - 1);
			if (b != NULL)
				this->tileLookUp->setFrequency(mapping[i], this->tileLookUp->getFrequency(mapping[i]) - 1);

		}
		char * a = strchr(this->myrackchars, BLANK_TILE);
		char * b = strchr(this->boardPool, BLANK_TILE);
		if(a!= NULL)
			this->tileLookUp->setFrequency(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE) - 1);
		if (b != NULL)
			this->tileLookUp->setFrequency(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE) - 1);

		for (int i = 0; i < size - 1; i++)
		{
			if (this->tileLookUp->getFrequency(mapping[i]) != 0)
			{
				this->availableFrequinces.push_back(std::make_pair(mapping[i], this->tileLookUp->getFrequency(mapping[i])));
				this->availableCharacters.push_back(mapping[i]);

			}
		}
		if (this->tileLookUp->getFrequency(BLANK_TILE) != 0)
		{
			this->availableFrequinces.push_back(std::make_pair(BLANK_TILE, this->tileLookUp->getFrequency(BLANK_TILE)));
			this->availableCharacters.push_back(BLANK_TILE);
		}

		delete this->tileLookUp;
		delete  a;
		delete b; 
		

}

vector<pair<vector<char>,double>> MonteCarlo::simulation(int N)
{
	this->createAvaliableLetters();
	vector<pair<vector<char>, double>> estimatedRackCost;
	for (int i = 0; i < N; i++) {
		 std::vector<char> temp = this->availableCharacters;
		 std::vector<char> rackgenerated;
		 for (int j = 0; j < 7; j++) {
			 const int range_from = 0;
			 const int range_to = temp.size()-1;
			 std::random_device                  rand_dev;
			 std::mt19937                        generator(rand_dev());
			 std::uniform_int_distribution<int>  distr(range_from, range_to);
			 int index = distr(generator);
			 rackgenerated.push_back(temp[index]);
			 temp.erase(temp.begin() + index);
		
		 }
		 sort(rackgenerated.begin(), rackgenerated.end());
		double value = Pm->calculateRackWeight(rackgenerated, this->availableFrequinces);
		// for (auto z = rackgenerated.begin(); z != rackgenerated.end(); ++z)
			// std::cout << *z << ' ';
		 //std::cout << value << endl;
		estimatedRackCost.push_back(std::make_pair(rackgenerated,value));
		 temp.clear();
		 rackgenerated.clear();
	}
	return estimatedRackCost;
}

MonteCarlo::~MonteCarlo()
{
}
