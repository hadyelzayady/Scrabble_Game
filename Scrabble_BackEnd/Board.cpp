#include "Board.h"

inline const char& Board::getLetter(int row, int column) const
{
	return board[row][column].letter;
}

inline bool Board::isEmptySquare(int row, int column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return board[row][column].isEmpty();
	}
	throw "array out of bound (Board-> isEmpty)";
}

Board::Board()
{
	cout << "Board initialising..." << endl;
	cout << "Board initialised" << endl;
}

Board::~Board()
{
}