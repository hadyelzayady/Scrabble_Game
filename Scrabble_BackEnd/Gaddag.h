#pragma once

#include "GaddagNode.h"
#include "move.h"
#include "Board.h"
#include <fstream>
#include <chrono>

class Gaddag {
public:
	GaddagNode*root;
	const char delimiter = '[';
	unsigned long buildtime;


	Gaddag(std::string path);

	GaddagNode* buildGaddag(std::ifstream& infile);

	GaddagNode* buildGaddagBranch(GaddagNode* root, std::string word);

	std::vector<std::string> traverse(GaddagNode* root);

	std::vector<Move> findWords(std::vector<char> rack, const Board& board);

	void findHorizontal(int offset, int anchorx, int anchory, Move inMove, std::vector<char> rack,
		GaddagNode* currNode, const Board& board, std::vector<Move>& moves);

	void goOnHorizontal(int offset, int anchorx, int anchory, char letter, Move inMove, std::vector<char> rack,
		GaddagNode* currNode, GaddagNode* nextNode, const Board& board, std::vector<Move>& moves);

	void findVertical(int offset, int anchorx, int anchory, Move inMove, std::vector<char> rack, GaddagNode* currNode,
		const Board & board, std::vector<Move>& moves);

	void goOnVertical(int offset, int anchorx, int anchory, char letter, Move inMove, std::vector<char> rack,
		GaddagNode* currNode, GaddagNode* nextNode, const Board& board, std::vector<Move>& moves);


	void eraseElementFromVector(std::vector<char> &vec, char value);
	
};
