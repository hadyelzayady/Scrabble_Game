#include "Heuristics.h"



const float vcvalues[8][8] =
{
	{  0.0,   0.0,  -1.0,  -2.5,  -5.0,  -8.5, -13.5, -18.5},
	{ -1.0,   0.0,   0.5,   0.0,  -1.5,  -5.0, -10.0,   0.0},
	{ -3.5,  -1.0,   0.5,   1.5,  -1.5,  -3.0,   0.0,   0.0},
	{ -7.0,  -3.5,  -0.5,   2.5,   0.0,   0.0,   0.0,   0.0},
	{-10.0,  -6.5,  -3.0,   0.0,   0.0,   0.0,   0.0,   0.0},
	{-13.5, -11.5,  -8.0,   0.0,   0.0,   0.0,   0.0,   0.0},
	{-18.5, -16.5,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0},
	{-23.5,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0},
};

Heuristics::Heuristics()
{

	ReadMap("double_RL.txt");


}
void Heuristics::ReadMap(string inDirectory)
{
	ifstream input(inDirectory);

	if (!input) cout << "Error occured while opening the file" << endl;
	else
	{

		while (!input.eof())
		{

			char ch;
			double cost;
			string total = "";
			input >> ch;
			total += ch;
			input >> ch;
			total += ch;
			input >> cost;

			double_RL[total] = cost;

		}
		input.close();
	}

}
double Heuristics::calculateDRL(vector<char> leave)
{
	double cost = 0.0;

	for (int i = 0; i < leave.size(); i++)
	{
		for (int j = i + 1; j < leave.size(); j++)
		{
			string x;
			string y;
			char c1 = leave[i];
			char c2 = leave[j];

			if (c1 == BLANK_TILE)
			{
				c1 = '?';
			}
			if (c2 == BLANK_TILE)
			{
				c2 = '?';
			}

			
				x.push_back(c2);
				x.push_back(c1);
			
				y.push_back(c1);
				y.push_back(c2);
			
				if (abs(double_RL[x]) >= abs(double_RL[y]))
				{
					cost += double_RL[x];
				}
				else
				{
					cost += double_RL[y];
				}
		}
	}

	return cost;

}
double Heuristics::getHeuristics(bool first_turn, vector<char> estimatedRack, Rack  current, Move  move, BagOfLetters bag, vector < pair<int, int>>  Qpos, vector < pair<int, int> > Zpos)
{
	
	vector<char> leave = current.getLeave(move); 
	vector<char> uniqleave = current.getUniqueLeave(move);

	if (bag.getSize() == 0) return endGame(estimatedRack, move, Qpos, Zpos);
	else if (bag.getSize() < 10 && bag.getSize() > 0) return preEnd(move, leave,uniqleave);
	else return midGame(first_turn, move, leave, uniqleave);

}
double Heuristics::endGame(vector<char> estimatedRack, Move move, vector<pair<int, int>>  Qpos, vector<pair<int, int>>  Zpos)
{
	double cost = 0.0;
	vector<Play> plays = move.getPlaysPointer();
	bool hasQ = false;
	bool hasZ = false;
	TileLookUp t;

	for (int i = 0; i < estimatedRack.size(); i++)
	{
		if (estimatedRack[i] == 'Q')hasQ = true;
		if (estimatedRack[i] == 'Z')hasZ = true;
	}
	int priority = 1;
	for (int i = 0; i < plays.size(); i++)
	{
		if (hasQ)
		{
			for (int k = 0; k < Qpos.size(); k++)
			{
				if (plays[i].get_Coordinates() == Qpos[k])
				{
					priority = priority + 0.2;
				}

			}

		}
		if (hasZ)
		{
			for (int k = 0; k < Zpos.size(); k++)
			{
				if (plays[i].get_Coordinates() == Zpos[k])
				{
					priority = priority + 0.2;
				}

			}
		}

		cost += t.getScore(plays[i].get_Letter());

	}

	cost = cost * priority;
	cost = cost * (1 - (plays.size() / 7)); //short word move has less cost than long word move

	return cost;
}
double Heuristics::preEnd(Move move, vector<char>  leave, vector<char> uniqleave)
{

	double cost = 0.0;
	int vowels = 0;
	int cons = 0;
	if (!leave.empty())
	{

		for (int i = 0; i < leave.size(); i++)
		{
			if (leave[i] != BLANK_TILE)
			{
				if (leave[i] == 'A' || leave[i] == 'E' || leave[i] == 'I' || leave[i] == 'O' || leave[i] == 'U')
					vowels++;
				else
					cons++;
			}
		}
		cost += vcvalues[vowels][cons]; //Reward 


		TileLookUp t;
		
		double synergy = calculateDRL(leave);
		synergy += calculateDRL(uniqleave);

		// TODO handle the Q
		bool holding_bad_tile = false;
		for (int i = 0; i < move.getPlaysPointer().size(); i++)
		{
			if (t.getScore(move.getPlaysPointer()[i].get_Letter()) > 7)
			{
				holding_bad_tile = true;
			}
		}
		if ((synergy > 3.0) && !holding_bad_tile) {
			synergy = synergy + 1.5 * (synergy - 3.0);
		}

		cost = cost + synergy;
	}



	return cost;
}
double Heuristics::midGame(bool first_turn, Move  move, vector<char> leave, vector<char> uniqleave)
{
	double cost = 0.0;
	vector<Play> plays = move.getPlaysPointer();
	if ( first_turn ==true)
	{
		if (plays.size() == 7)
		{
			cost -= 50;
		}
	}
	int vowels = 0;
	int cons = 0;

	if (!leave.empty())
	{

		for (int i = 0; i < leave.size(); i++)
		{
			if (leave[i] != BLANK_TILE)
			{
				if (leave[i] == 'A' || leave[i] == 'E' || leave[i] == 'I' || leave[i] == 'O' || leave[i] == 'U')
					vowels++;
				else
					cons++;
			}
		}
		cost += vcvalues[vowels][cons];


		TileLookUp t;
		
		double synergy = calculateDRL(leave);
		synergy += calculateDRL(uniqleave);

		// TODO handle the Q
		bool holding_bad_tile = false;
		for (int i = 0; i < move.getPlaysPointer().size(); i++)
		{
			if (t.getScore(move.getPlaysPointer()[i].get_Letter()) > 7)
			{
				holding_bad_tile = true;
			}
		}
		if ((synergy > 3.0) && !holding_bad_tile) {
			synergy = synergy + 1.5 * (synergy - 3.0);
		}

		cost = cost + synergy;
	}



	return cost;
}

Heuristics::~Heuristics()
{
}


