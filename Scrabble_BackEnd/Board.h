#pragma once
#include <vector>
#include "Square.h"
#include "Constants.h"
#include <iostream>
using namespace std;
#include <string>
#include "move.h"
class Board
{
	string LettersOnBoard;
  public:
	  Square m_board[ROWS_COUNT][COLUMNS_COUNT] = { {} };
	inline const string& getBoardLetters();
	void commitMove(const Move& move);
	Board commitMoveSim(const Move& move);
	inline const char &getLetter(unsigned short row, unsigned short column) const;
	inline bool isEmptySquare(unsigned short row, unsigned short column) const; //same as square.isEmpty just another interface
	//bool isConnected(const Move);

	Board(const Square board[ROWS_COUNT][COLUMNS_COUNT]);
	Board();
	void setTile(char letter, unsigned short row, unsigned short column);
	//static void setTileSim(char letter, unsigned short row, unsigned short column, Square m_board[ROWS_COUNT][COLUMNS_COUNT]);
	void updateAnchors(std::string move); //TODO : parameter should be Move objedut this is for testing
	inline bool isHook(unsigned short row, unsigned short column) const;
	inline bool isAnchor(unsigned short row, unsigned short column) const;
	//TODO in B* simu: the node is board state and the arch is the move
	~Board();
};
