#include "Gaddag.h"

Gaddag::Gaddag(std::string path) {
	char x = ' ';
	root = new GaddagNode(x);
	buildtime =
		(unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
	std::ifstream infile(path);
	if (infile.fail()) {
		std::cout << "file does not exists" << std::endl;
	}
	else {
		buildGaddag(infile);

		infile.close();
		std::cout << "Done!" << std::endl;
		unsigned long currentTime =
			(unsigned long)std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();
		std::cout << "Build time: ";
		std::cout << (currentTime - buildtime) / (1000.0) << std::endl;
		std::cout << "Nodes: ";
		std::cout << GaddagNode::idCounter << std::endl;
	}
}

GaddagNode* Gaddag::buildGaddag(std::ifstream& infile)
{
	GaddagNode * node = root;
	std::cout << "Building gaddag: " << std::endl;
	std::string word;
	int line = 0;
	while (std::getline(infile, word)) {
		line++;
		//std::cout << "line # = ";
		//std::cout << line<<std::endl;
		//std::cout <<"word= " + word << std::endl;

		std::string tempWord = word;
		std::reverse(tempWord.begin(), tempWord.end());
		buildGaddagBranch(node, tempWord);
		tempWord = word.substr(0, word.length() - 1);
		std::reverse(tempWord.begin(), tempWord.end());
		tempWord = tempWord + delimiter + word.substr(word.length() - 1);
		node = buildGaddagBranch(node, tempWord);
		for (int j = word.length() - 3; j >= 0; j--) {
			GaddagNode* temp = node;
			node = root;
			for (int i = j; i >= 0; --i) {
				node = node->putTransitionChar(word[i], NULL);
			}
			node = node->putTransitionChar(delimiter, NULL);
			node->putTransitionChar(word[j + 1], temp);
		}
	}
	std::cout << "Building done!" << std::endl;
	return root;
}

GaddagNode* Gaddag::buildGaddagBranch(GaddagNode* root, std::string word) {
	GaddagNode *current = root;
	for (int i = 0, ilen = word.length() - 1; i < ilen; ++i) {
		current = current->putTransitionChar(word[i], NULL);
		if (i == word.length() - 2) {
			current->putEnd(word[word.length() - 1]);
		}
	}
	return current;
}

//std::vector<std::string> Gaddag::traverse(GaddagNode* root) {
//	std::vector<std::string>words;
//	std::vector<unsigned int> indexTransition;
//	std::vector<unsigned int> indexEnd;
//	root->getOnesPositions(root->transitions, indexTransition);
//	root->getOnesPositions(root->end, indexEnd);
//	for (unsigned int i : indexTransition) {
//		GaddagNode* child = root->children[i];
//		if (child == NULL)
//			continue;
//		for (std::string s : traverse(child)) {
//			words.push_back("" + mapping[i] + s);
//		}
//	}
//	for (unsigned int i : indexEnd) {
//		words.push_back("" + mapping[i]);
//	}
//	return words;
//}

