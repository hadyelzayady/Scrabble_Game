#pragma once

#include "GaddagNode.h"
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



};
