#include "Square.h"

Square::Square(BonusSquareType bType)
{
	bonusType = bType;
	letter = EMPTY_SQUARE;
}

Square::~Square()
{
}