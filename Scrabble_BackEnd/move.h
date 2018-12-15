#pragma once
#include "Play.h"
#include<vector>
class Move
{
	
public:
	vector< Play>  Plays;
	vector<char> chars;
	bool isBingo;
	vector<Play> getPlaysPointer() const;
	void setBingo(bool bingo);
	bool getBingo();
	void addPlay(Play play);
	void addPlay(int x, int y, char l, bool blank = false);
	void  setPlayPointer(vector<Play> Plays);
	Move();
	Move(const Move& other);
	~Move();
};

