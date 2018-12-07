#include "BStarNode.h"



BStarNode::BStarNode(double opt, double pess, int id,const Move& move)
{
	this->optm = opt;
	this->pess = pess;
	this->id = id;
	this->move = move;
}

BStarNode::BStarNode()
{
	this->optm = -1;
	this->pess = -1;
	this->id = -1;
}


BStarNode::~BStarNode()
{
}
