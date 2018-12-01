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
	static Square BoardForm[ROWS_COUNT][COLUMNS_COUNT];
	Square m_board[ROWS_COUNT][COLUMNS_COUNT];
	const string& getBoardLetters();
	void commitMove(const Move& move);
	static Board  commitMoveSim(const Move & move, Board board);
	Board  commitMoveSimB(const Move& move);
	void  commitMoveSimC(const Move& move,Board& newBoard);
	const char &getLetter(unsigned short row, unsigned short column) const;
	bool isEmptySquare(unsigned short row, unsigned short column) const; //same as square.isEmpty just another interface
	//bool isConnected(const Move);
	Board(const Square board[ROWS_COUNT][COLUMNS_COUNT]);
	Board();
	Board(const Board & b);
	void setTile(char letter, unsigned short row, unsigned short column);
	//static void setTileSim(char letter, unsigned short row, unsigned short column, Square m_board[ROWS_COUNT][COLUMNS_COUNT]);
	bool isHook(unsigned short row, unsigned short column) const;//letter on board that has at least one empty square around it
	bool isAnchor(unsigned short row, unsigned short column) const;//empty square on board that has at least one letter around it
	//TODO in B* simu: the node is board state and the arch is the move
	~Board();
};
