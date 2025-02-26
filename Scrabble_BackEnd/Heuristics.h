#pragma once
#include "Rack.h"
#include "move.h"
#include "BagOfLetters.h"
#include "TileLookUp.h"
#include <map>
#include <algorithm>
#include <string>
#include <fstream>


class Heuristics
{
	map<string, double> double_RL;
	map<string, double> leave_DP;

	public:
	Heuristics();
	double getHeuristics(bool first_turn, vector<char> estimatedRack, Rack  current, Move  move, BagOfLetters bag, vector < pair<int, int>>Qpos, vector < pair<int, int>> Zpos);
	double endGame(vector<char> estimatedRack, int currentRack_size, Move move, vector<pair<int, int>> Qpos, vector<pair<int, int>> Zpos);
	double VowelCons(vector<char> leave);
	double SlowEndGame(int currentRack_size, int move_size);
	double preEnd(Move move, vector<char>  leave, vector<char> uniqleave);
	double midGame(bool first_turn, Move  move, vector<char> leave, vector<char> uniqleave);
	void endGame2vals(vector<char> estimatedRack, Rack current, Move move, vector<pair<int, int>> Qpos, vector<pair<int, int>> Zpos, double & maxVal, double & minVal);
	void ReadMap(string inDirectory);
	void Read_Leave_DP();
	void saveToFile(vector<char> data, double cost);
	double calculateDRL(vector<char> leave);
	double Double_RL(Move move, vector<char> leave, vector<char> uniqleave);
	double Qsticking(vector<char> estimatedRack, Move move, vector<pair<int, int>>  Qpos, vector<pair<int, int>>  Zpos);

	~Heuristics();
};




