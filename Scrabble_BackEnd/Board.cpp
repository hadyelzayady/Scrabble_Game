#include "Board.h"

inline const char &Board::getLetter(unsigned short row, unsigned short column) const
{
	return m_board[row][column].letter;
}

inline bool Board::isEmptySquare(unsigned short row, unsigned short column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return m_board[row][column].isEmpty();
	}
	throw EXCEPTION_OUT_OF_BOUND;
}

Board::Board(const Square board[ROWS_COUNT][COLUMNS_COUNT])
{
	try
	{
		for (size_t i = 0; i < ROWS_COUNT; i++)
			for (size_t j = 0; j < COLUMNS_COUNT; j++)
			{
				m_board[i][j] = board[i][j];
			}
	}
	catch (...)
	{
		throw "error in board init";
	}
}
//exectued after each play
void updateAnchors(std::string letters, int positions[3][3])
{
	//map table, letter :array of positions
	//iterate over characters of newly created words and update the anchor. (newly created words includes other connected chars)
	// ? why not anchors are array of positions as we can get letter by poistion!
	// if we return letter then we iterate over small array which will have high probability of existance in cache!
}
Board::Board()
{
}

void Board::setTile(char letter, unsigned short row, unsigned short column)
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		m_board[row][column].letter = letter;
	}
	throw EXCEPTION_OUT_OF_BOUND;
}

inline bool Board::isHook(unsigned short row, unsigned short column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return !m_board[row][column].isEmpty() ||
			   ((column < COLUMNS_COUNT - 1) && m_board[row][column + 1].isEmpty()) || // right
			   ((column > 0) && m_board[row][column - 1].isEmpty()) ||				   // left
			   ((row > 0) && m_board[row - 1][column].isEmpty()) ||					   // top
			   ((column < ROWS_COUNT - 1) && m_board[row + 1][column].isEmpty())	   // down
			;
	}
	throw EXCEPTION_OUT_OF_BOUND;
}
inline bool Board::isAnchor(unsigned short row, unsigned short column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return m_board[row][column].isEmpty() &&
				   ((column < COLUMNS_COUNT - 1) && !m_board[row][column + 1].isEmpty()) || // right
			   ((column > 0) && !m_board[row][column - 1].isEmpty()) ||						// left
			   ((row > 0) && !m_board[row - 1][column].isEmpty()) ||						// top
			   ((row < ROWS_COUNT - 1) && !m_board[row + 1][column].isEmpty())				// down
			;
	}
	throw EXCEPTION_OUT_OF_BOUND;
}

Board::~Board()
{
}