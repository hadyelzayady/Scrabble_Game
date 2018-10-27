#pragma once
#include <vector>
#include "Square.h"
#include "Constants.h"
#include <iostream>
using namespace std;
class Board
{
public:
	Square board[ROWS_COUNT][COLUMNS_COUNT];
	inline const char& getLetter(int row, int column)const;
	inline bool isEmptySquare(int row, int column) const;
	//bool isConnected(const Move);
	Board();
	~Board();
};
