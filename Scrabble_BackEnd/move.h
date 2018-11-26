#pragma once
#include "Play.h"
#include<vector>
class Move
{
	
public:
	vector< Play>  Plays;
	int score;
	bool isBingo;
	vector<Play> getPlaysPointer();
	void setBingo(bool bingo);
	bool getBingo();
	void setScore(int score);
	int getScore();
	void addPlay(Play play);
	void addPlay(int x, int y, char l, bool blank = false);
	void  setPlayPointer(vector<Play> Plays);
	Move();
	Move(const Move& other);
	~Move();
};

