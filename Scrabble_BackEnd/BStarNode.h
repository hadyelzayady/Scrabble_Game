#pragma once
#include "Board.h"

class BStarNode
{

	public:
		int optm;
		int pess;
		int id;
		Move move;//move that lead to this node from parent
		bool closed = false;
		BStarNode(int opt, int pess, int id,const Move& move);
		BStarNode();
		~BStarNode();
};

