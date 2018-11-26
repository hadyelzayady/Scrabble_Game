#pragma once
#include "Constants.h"

enum BonusSquareType { NoBonus = 0, LetterBonusX2, LetterBonusX3, WordBonusX2, WordBonusX3 };

class Square
{

public:
	char letter = EMPTY_SQUARE;//! blank tile has special character (check in constants file) , empty square equals null
	
	// ToDo: we can make new class inherits from this class to contain below data members 
	// as many squares are not prime squares in the boad so we will save space
	short points = 0;
	
	//also it can be boolean with points=0 for no bonus but using enum is more clear
	BonusSquareType bonusType;
	
	Square(BonusSquareType bType = NoBonus);
	inline bool isEmpty() const {
		return letter == EMPTY_SQUARE;
	}
	~Square();
};
