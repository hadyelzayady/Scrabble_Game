
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
double Heuristics::calculateDRL(const vector<char>& leave)
{
	double cost = 0.0;
	int i, ilen;
	for ( i=0,ilen=leave.size(); i < ilen; i++)
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
double Heuristics::getHeuristics(bool first_turn, const vector<char>& estimatedRack, const Rack&  current,const Move&  move,const BagOfLetters& bag, const vector < pair<int, int>>&  Qpos, const vector < pair<int, int>> & Zpos)
{
	
	vector<char> leave = current.getLeave(move); 
	vector<char> uniqleave = current.getUniqueLeave(move);

	if (bag.size == 0) return endGame(estimatedRack, move, Qpos, Zpos);
	else if (bag.size < 10 && bag.size > 0) return preEnd(move, leave,uniqleave);
	else return midGame(first_turn, move, leave, uniqleave);

}
double Heuristics::endGame(const  vector<char>& estimatedRack, const Move& move, const vector<pair<int, int>>&  Qpos, const vector<pair<int, int>>&  Zpos)
{
	double cost = 0.0;
	//vector<Play> plays = move.getPlaysPointer();
	bool hasQ = false;
	bool hasZ = false;
	TileLookUp t;
	int i, ilen;
	for (i = 0,ilen= estimatedRack.size(); i < ilen; i++)
	{
		if (estimatedRack[i] == 'Q')hasQ = true;
		if (estimatedRack[i] == 'Z')hasZ = true;
	}
	int priority = 1;
	for ( i = 0,ilen=move.Plays.size(); i < ilen; i++)
	{
		if (hasQ)
		{
			int k, klen;
			for ( k = 0,klen= Qpos.size(); k < klen; k++)
			{
				if (move.Plays[i].coordinates == Qpos[k])
				{
					priority = priority + 0.2;
				}

			}

		}
		if (hasZ)
		{
			int k, klen;
			for ( k = 0,klen=Zpos.size(); k < klen; k++)
			{
				if (move.Plays[i].coordinates == Zpos[k])
				{
					priority = priority + 0.2;
				}

			}
		}

		cost += t.getScore(move.Plays[i].Letter);

	}

	cost = cost * priority;
	cost = cost * (1 - (move.Plays.size() / 7)); //short word move has less cost than long word move

	return cost;
}
double Heuristics::preEnd(const Move& move, const vector<char>&  leave, const vector<char>& uniqleave)
{

	double cost = 0.0;
	int vowels = 0;
	int cons = 0;
	if (!leave.empty())
	{
		int i, ilen;
		for ( i = 0,ilen=leave.size(); i < ilen; i++)
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
		for ( i = 0,ilen=move.Plays.size(); i < ilen; i++)
		{
			if (t.getScore(move.Plays[i].Letter) > 7)
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
double Heuristics::midGame(bool first_turn, const Move&  move, const vector<char>& leave, const vector<char>& uniqleave)
{
	double cost = 0.0;
	//vector<Play> plays = move.getPlaysPointer();
	if ( first_turn ==true)
	{
		if (move.Plays.size() == 7)
		{
			cost -= 50;
		}
	}
	int vowels = 0;
	int cons = 0;

	if (!leave.empty())
	{
		int i, ilen;
		for ( i = 0,ilen= leave.size(); i < ilen; i++)
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

		for (i = 0,ilen= move.Plays.size(); i < ilen; i++)
		{
			if (t.getScore(move.Plays[i].Letter) > 7)
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