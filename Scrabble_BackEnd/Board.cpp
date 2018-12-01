#include "Board.h"
Square Board::BoardForm[ROWS_COUNT][COLUMNS_COUNT] = { {Square(LetterBonusX3),Square(NoBonus),Square(NoBonus),
		Square(LetterBonusX2),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(LetterBonusX3),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX3)}
	,{Square(NoBonus),Square(LetterBonusX2),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},{
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)} };
//TODO: blank letters should be added in board letter	
const string &Board::getBoardLetters()
{
	// TODO: insert return statement here
	return LettersOnBoard;
}
//we added board as parameter so we can use it inside commitMoveSim
void Board::commitMove(const Move &move)
{
	vector<Play>plays = move.getPlaysPointer();
	for (size_t i = 0; i < plays.size(); i++)
	{
		char letter = plays[i].get_Letter();
		pair<int, int> position = plays[i].get_Coordinates();
		setTile(letter, position.first, position.second);
		//
		LettersOnBoard+=letter;
	}
}
//?we use commitMoveSim instead of commitMove as we return new board with move changes and no effect happens to the original board
Board Board::commitMoveSimB(const Move &move)
{
	Board newBoard(m_board);
	newBoard.commitMove(move);
	return newBoard; //? still not sure if we should return 2d array or board object but soliman needs board object to get moves
}
//we use commitMoveSim instead of commitMove as we return new board with move changes and no effect happens to the original board
Board Board::commitMoveSim(const Move & move, Board board)
{
	Board  * B = new Board(board);
	B->commitMove(move);
	return *B;
}

 const char &Board::getLetter(unsigned short row, unsigned short column) const
{
	return m_board[row][column].letter;
}

 bool Board::isEmptySquare(unsigned short row, unsigned short column) const
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
		LettersOnBoard = "";
		for (size_t i = 0; i < ROWS_COUNT; i++)
			for (size_t j = 0; j < COLUMNS_COUNT; j++)
			{
				m_board[i][j] = board[i][j];
				if (!m_board[i][j].isEmpty())
					LettersOnBoard+=m_board[i][j].letter;
			}
	}
	catch (...)
	{
		throw "error in board init";
	}
}
Board::Board()
{
	for (size_t i = 0; i < ROWS_COUNT; i++)
		for (size_t j = 0; j < COLUMNS_COUNT; j++)
		{
			m_board[i][j] = Board::BoardForm[i][j];
		}
	LettersOnBoard = "";
}

Board::Board(const Board&b) {
	for (size_t i = 0; i < ROWS_COUNT; i++)
		for (size_t j = 0; j < COLUMNS_COUNT; j++)
		{
			m_board[i][j] = b.m_board[i][j];
			if (!m_board[i][j].isEmpty())
				LettersOnBoard+=m_board[i][j].letter;
		}
}


void Board::setTile(char letter, unsigned short row, unsigned short column)
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		m_board[row][column].letter = letter;
		return;
	}
	throw EXCEPTION_OUT_OF_BOUND;
}

 bool Board::isHook(unsigned short row, unsigned short column) const
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
 bool Board::isAnchor(unsigned short row, unsigned short column) const
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