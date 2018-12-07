#pragma once
#include "Board.h"

class BStarNode
{

	public:
		double optm;
		double pess;
		int id;
		Move move;//move that lead to this node from parent
		bool closed = false;
		BStarNode(double opt, double pess, int id,const Move& move);
		BStarNode();
		~BStarNode();
};

