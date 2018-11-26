#pragma once
#include <iostream>
using namespace std;
class Play
{

private:
	char Letter;
	pair<int, int> coordinates;
	bool Blank;
	int Index;
public:
	pair<int, int> get_Coordinates();
	void set_Coordinates(pair<int, int> coordinates);
	void set_Letter(char Letter,int index,bool blank = false);
	bool isBlank();
	int get_Index(int index);
	char get_Letter();
	Play();
	Play(int x, int y, char l,bool blank = false);
	~Play();
};

