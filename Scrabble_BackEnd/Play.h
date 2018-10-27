#pragma once
#include <iostream>
using namespace std;
class Play
{

private:
	char Letter;
	pair<int, int> cooridantes;
public:
	pair<int, int> get_Cooridantes();
	void set_Cooridantes(pair<int, int> Corridantes);
	void set_Letter(char Letter);
	char get_Letter();
	Play();
	~Play();
};

