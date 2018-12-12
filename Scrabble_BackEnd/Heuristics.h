#pragma once
#include "Rack.h"
#include "move.h"
#include "BagOfLetters.h"
#include "TileLookUp.h"
#include <map>
#include <fstream>


class Heuristics
{
	map<string, double> double_RL;
public:
	Heuristics();
	double getHeuristics(bool first_turn, const vector<char>& estimatedRack, const Rack&  current, const Move&  move, const BagOfLetters& bag, const vector < pair<int, int>> & Qpos,const vector < pair<int, int>>& Zpos);
	double endGame(const vector<char>& estimatedRack, const Move& move,const vector<pair<int, int>>&  Qpos,const vector<pair<int, int>>&  Zpos);
	double preEnd(const Move& move, const vector<char>&  leave, const vector<char>& uniqleave);
	double midGame(bool first_turn,const Move&  move, const vector<char>& leave,const vector<char>& uniqleave);
	void ReadMap(string inDirectory);
	double calculateDRL(const vector<char>& leave);

	~Heuristics();
};




