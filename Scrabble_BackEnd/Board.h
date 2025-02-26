#pragma once
#include <vector>
#include "Square.h"
#include "Constants.h"
#include <iostream>
#include "GaddagNode.h"
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
	void commitMoves(const vector<Move>& moves);
	static Board  commitMoveSim(const Move & move, Board board);
	Board  commitMoveSimB(const Move& move);
	void  commitMoveSimC(const Move& move,Board& newBoard);
	void UnCommitMove(const Move& move);
	const char &getLetter(unsigned short row, unsigned short column) const;
	bool isEmptySquare(unsigned short row, unsigned short column) const; //same as square.isEmpty just another interface
	//bool isConnected(const Move);
	Board(const Square board[ROWS_COUNT][COLUMNS_COUNT]);
	Board();
	Board(const Board & b);
	void setTile(char letter, unsigned short row, unsigned short column);
	void removeTile(unsigned short row, unsigned short column);
	//static void setTileSim(char letter, unsigned short row, unsigned short column, Square m_board[ROWS_COUNT][COLUMNS_COUNT]);
	bool isHook(unsigned short row, unsigned short column) const;//letter on board that has at least one empty square around it
	bool isAnchor(unsigned short row, unsigned short column) const;//empty square on board that has at least one letter around it
	//TODO in B* simu: the node is board state and the arch is the move

	//Timon Updates
	void computeCrossSets( GaddagNode* g);  /// g is the root in gaddag class 

	void computeHorizontalSet(int i, int j, GaddagNode* root);
	void computeVerticalSet(int i, int j, GaddagNode* root);

	bool checkCharInHorizontalSet(int i, int j, char l) const;
	bool checkCharInVerticalSet(int i, int j, char l) const;


	~Board();
};
