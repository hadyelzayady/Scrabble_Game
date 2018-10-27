#pragma once
#include <vector>
#include "Square.h"
#include "Constants.h"
#include <string>
class Board
{
  public:
	Square m_board[ROWS_COUNT][COLUMNS_COUNT];
	inline const char &getLetter(unsigned short row, unsigned short column) const;
	inline bool isEmptySquare(unsigned short row, unsigned short column) const; //same as square.isEmpty just another interface
	//bool isConnected(const Move);
	Board(const Square board[ROWS_COUNT][COLUMNS_COUNT]);
	Board();
	void setTile(char letter, unsigned short row, unsigned short column);
	void updateAnchors(std::string move); //TODO : parameter should be Move objedut this is for testing
	inline bool isHook(unsigned short row, unsigned short column) const;
	inline bool isAnchor(unsigned short row, unsigned short column) const;
	~Board();
};
