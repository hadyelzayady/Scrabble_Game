#pragma once
#include "Board.h"

class BStarNode
{

	public:
		int optm;
		int pess;
		int id;
		Board board;
		Move move;
		bool closed = false;
		BStarNode(int opt, int pess, int id, Board board, Move move);
		BStarNode();
		~BStarNode();
};

