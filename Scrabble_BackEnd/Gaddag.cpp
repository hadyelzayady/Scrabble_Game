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
	GaddagNode * node ;
	std::cout << "Building gaddag: " << std::endl;
	std::string word;
	int line = 0;
	while (std::getline(infile, word)) {
		node = root;
		//line++;
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

std::vector<std::string> Gaddag::traverse(GaddagNode* root) {

	std::vector<std::string>words;

	std::vector<unsigned int> indexTransition;
	std::vector<unsigned int> indexEnd;
	root->getOnesPositions(root->transitions, indexTransition);
	root->getOnesPositions(root->end, indexEnd);
	for (unsigned int i : indexTransition) {
		GaddagNode* child = root->children[i];
		if (child == NULL)
			continue;
		for (std::string s : traverse(child)) {
			std::string word = std::string(1, mapping[i]) + s;
			words.push_back(word);
		}
	}
	for (unsigned int i : indexEnd) {
		std::string word = std::string(1, mapping[i]);
		words.push_back(word);
	}
	return words;
}


std::vector<Move> Gaddag::findWords(std::vector<char> rack, Board* board) {
	std::vector<Move> moves;
	
	for (int j = 0; j < ROWS_COUNT; j++) {
		for (int i = 0; i < COLUMNS_COUNT; i++) {
			if (board->isAnchor(i,j) ){	
				Move z;
				Move y;
				findHorizontal(0, j, i, z, rack, root, board, moves);
				findVertical(0, j, i, y, rack, root, board, moves);
			}
		}
	}
	return moves;
}

void Gaddag::findHorizontal(int offset, int anchorx, int anchory, Move inMove, std::vector<char> rack,
	GaddagNode* currNode, Board* board, std::vector<Move>& moves) {

	if (anchorx + offset >= COLUMNS_COUNT || anchorx + offset < 0)
		return;

	if (!board->isEmptySquare(anchory,anchorx+offset )) {		//if there is a tile in the square to the left we must include this in the current move
		char l = board->getLetter(anchory, anchorx + offset);
		GaddagNode* nextNode = currNode->getChildren(l);
		Move newMove(inMove);
		//newMove.addPlay(anchorx + offset, anchory, l);
		goOnHorizontal(offset, anchorx, anchory, l, newMove, rack, currNode, nextNode, board, moves);	//move on to the next square
	}
	else if (rack.size()!=0) {	//else if we still have letters we can play
		int i, ilen ;
		for (i = 0, ilen = rack.size(); i < ilen; ++i) {
			if (rack[i] != BLANK_TILE && board->checkCharInVerticalSet(anchory, anchorx + offset,rack[i])) {	//if not blank + is legal to play in next square
				std::vector<char> newRack = rack;
				eraseElementFromVector(newRack, rack[i]);
				GaddagNode* nextNode = currNode->getChildren(rack[i]);
				Move newMove(inMove);
				newMove.addPlay(anchorx + offset, anchory, rack[i]);
				goOnHorizontal(offset, anchorx, anchory, rack[i], newMove, newRack, currNode, nextNode, board, moves);
			}
			else
			{
				/// to be implemented
			}

		}

	}
}






 void Gaddag::goOnHorizontal(int offset, int anchorx, int anchory, char letter, Move inMove, std::vector<char> rack,
	 GaddagNode* currNode, GaddagNode* nextNode, Board * board, std::vector<Move>& moves){
	if (offset <= 0) {	//if making prefix
		//if its a valid move ending record it
		if (currNode->hasCharAsEnd(letter) && board->isEmptySquare(anchory,anchorx+offset-1)&& board->isEmptySquare(anchory, anchorx + 1)) {
			if (rack.size()==0)
				inMove.isBingo = true;
			moves.push_back(inMove);
		}

		//continue trying to generate prefixes passing nextNode as currNode
		if (nextNode != NULL) {
			findHorizontal(offset - 1, anchorx, anchory, inMove, rack, nextNode, board, moves);

			//if we can start making suffixes do so
			nextNode = nextNode->getChildren('[');  /// msh mesta5dem el const 3shan da el mafrood yb2a delimeter msh blank bas homa nafs el char 3shan el ma3na msh aktar 
			if (nextNode != NULL && board->isEmptySquare(anchory,anchorx+offset-1)) {
				findHorizontal(1, anchorx, anchory, inMove, rack, nextNode, board, moves);
			}
		}
	}
	else if (offset > 0) {	//else if making suffix
		//if its a valid move ending record it
		if (currNode->hasCharAsEnd(letter) && board->isEmptySquare(anchory, anchorx + offset + 1)) {
			if (rack.size()==0)
				inMove.isBingo = true;
			moves.push_back(inMove);
		}
		if (nextNode != NULL /*&& board.isEmptySquare(anchory,anchorx+offset+1)*/) {
			//continue trying to generate suffixes
			findHorizontal(offset + 1, anchorx, anchory, inMove, rack, nextNode, board, moves);
		}
	}
}

 void Gaddag::findVertical(int offset, int anchorx, int anchory, Move inMove, std::vector<char> rack, GaddagNode* currNode,
	 Board * board, std::vector<Move>& moves) {

	 if (anchory + offset >= ROWS_COUNT || anchory + offset < 0)
		 return;

	 if (!board->isEmptySquare(anchory+offset,anchorx)) {		//if there is a tile in the square to the left we must include this in the current move
		 char l = board->getLetter(anchory + offset, anchorx);
		 GaddagNode* nextNode = currNode->getChildren(l);
		 Move newMove(inMove);
		 //newMove.addPlay(anchorx, anchory + offset, l);
		 goOnVertical(offset, anchorx, anchory, l, newMove, rack, currNode, nextNode, board, moves);	//move on to the next square
	 }
	 else if (rack.size()!=0) {	//else if we still have letters we can play
		 int i, ilen;
		 for (i = 0, ilen = rack.size(); i < ilen; ++i) {
			 if (rack[i] != BLANK_TILE && board->checkCharInHorizontalSet(anchory + offset, anchorx,rack[i] )) {	//if not blank + is legal to play in next square
				 std::vector<char> newRack = rack;
				 eraseElementFromVector(newRack, rack[i]);
				 GaddagNode* nextNode = currNode->getChildren(rack[i]);
				 Move newMove(inMove);
				 newMove.addPlay(anchorx, anchory + offset, rack[i]);
				 goOnVertical(offset, anchorx, anchory, rack[i], newMove, newRack, currNode, nextNode, board, moves);
			 }
			 else{
				 /// to be implemented
		 }

	 }
	}
 }

 void Gaddag::goOnVertical(int offset, int anchorx, int anchory, char letter, Move inMove, std::vector<char> rack,
	 GaddagNode* currNode, GaddagNode* nextNode, Board* board, std::vector<Move>& moves) {

	 if (offset <= 0) {	//if making prefix
			//if its a valid move ending record it			
		 if (currNode->hasCharAsEnd(letter) && board->isEmptySquare(anchory + offset - 1, anchorx) && board->isEmptySquare(anchory+1,anchorx)) {
			 if (rack.size()==0)
				 inMove.isBingo = true;
			 moves.push_back(inMove);
		 }

		 //continue trying to generate prefixes passing nextNode as currNode
		 if (nextNode != NULL) {
			 findVertical(offset - 1, anchorx, anchory, inMove, rack, nextNode, board, moves);

			 //if we can start making suffixes do so
			 nextNode = nextNode->getChildren('[');
			 if (nextNode != NULL && board->isEmptySquare(anchory + offset - 1, anchorx )) {
				 findVertical(1, anchorx, anchory, inMove, rack, nextNode, board, moves);

			 }
		 }
	 }
	 else if (offset > 0) {	//else if making suffix
		 //if its a valid move ending record it
		 if (currNode->hasCharAsEnd(letter) && board->isEmptySquare(anchory + offset + 1, anchorx )) {
			 if (rack.size()==0)
				 inMove.isBingo = true;
			 moves.push_back(inMove);
		 }
		 if (nextNode != NULL /*&& board.isEmptySquare(anchory + offset + 1, anchorx)*/) {
			 //continue trying to generate suffixes
			 findVertical(offset + 1, anchorx, anchory, inMove, rack, nextNode, board, moves);
		 }
	 }
 }



 void Gaddag::eraseElementFromVector(std::vector<char> &vec, char value)
 {
	 // get the range in 2*log2(N), N=vec.size()
	 auto bounds = std::equal_range(vec.begin(), vec.end(), value);

	 // calculate the index of the first to be deleted O(1)
	 auto last = vec.end() - std::distance(bounds.first, bounds.second);

	 // swap the 2 ranges O(equals) , equal = std::distance(bounds.first, bounds.last)
	 std::swap_ranges(bounds.first, bounds.second, last);

	 // erase the victims O(equals)
	 vec.erase(last, vec.end());
 }
