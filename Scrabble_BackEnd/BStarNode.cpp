#include "BStarNode.h"



BStarNode::BStarNode(int opt, int pess, int id, Board board, Move move)
{
	this->optm = opt;
	this->pess = pess;
	this->id = id;
	this->board = board;
	this->move = move;
}


BStarNode::~BStarNode()
{
}
