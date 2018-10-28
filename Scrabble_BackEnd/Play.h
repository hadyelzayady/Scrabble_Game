#pragma once
#include <iostream>
using namespace std;
class Play
{

private:
	char Letter;
	pair<int, int> coordinates;
public:
	pair<int, int> get_Coordinates();
	void set_Coordinates(pair<int, int> coordinates);
	void set_Letter(char Letter);
	char get_Letter();
	Play();
	~Play();
};

