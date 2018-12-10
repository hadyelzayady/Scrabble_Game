#include "Board.h"
Square Board::BoardForm[ROWS_COUNT][COLUMNS_COUNT] = {
		{Square(WordBonusX3),Square(NoBonus),Square(NoBonus),
		Square(LetterBonusX2),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX3),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(WordBonusX3)}
	,{Square(NoBonus),Square(WordBonusX2),Square(NoBonus),
		Square(NoBonus),Square(NoBonus),Square(LetterBonusX3)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX3),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX2),Square(NoBonus)},
	{Square(NoBonus),Square(NoBonus),Square(WordBonusX2),
		Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX2),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(WordBonusX2),Square(NoBonus),Square(NoBonus)},
	{Square(LetterBonusX2),Square(NoBonus),Square(NoBonus),
		Square(WordBonusX2),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(LetterBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(WordBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX2)},
	{Square(NoBonus),Square(NoBonus),Square(NoBonus),
		Square(NoBonus),Square(WordBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)},
	{Square(NoBonus),Square(LetterBonusX3),Square(NoBonus),
		Square(NoBonus),Square(NoBonus),Square(LetterBonusX3)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX3),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(LetterBonusX3),Square(NoBonus)},
	{Square(NoBonus),Square(NoBonus),Square(LetterBonusX2),
		Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX2),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX2),Square(NoBonus),Square(NoBonus)},
	{Square(WordBonusX3),Square(NoBonus),Square(NoBonus),
		Square(LetterBonusX2),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(WordBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},{
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)},
	{Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3),
		Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)
		,Square(LetterBonusX3),Square(LetterBonusX3),Square(LetterBonusX3)} };
//TODO: blank letters should be added in board letter	
const string &Board::getBoardLetters()
{
	// TODO: insert return statement here
	return LettersOnBoard;
}
//we added board as parameter so we can use it inside commitMoveSim
void Board::commitMove(const Move &move)
{
	vector<Play>plays = move.Plays;
	for (size_t i = 0; i < plays.size(); i++)
	{
		char letter = plays[i].get_Letter();
		pair<int, int> position = plays[i].get_Coordinates();
		setTile(letter, position.second, position.first);
		//
		LettersOnBoard += letter;
	}
}
//?we use commitMoveSim instead of commitMove as we return new board with move changes and no effect happens to the original board
/*Board Board::commitMoveSimB(const Move &move)
{
	Board newBoard(m_board);
	newBoard.commitMove(move);
	return newBoard; //? still not sure if we should return 2d array or board object but soliman needs board object to get moves
}*/
//we use commitMoveSim instead of commitMove as we return new board with move changes and no effect happens to the original board
Board Board::commitMoveSim(const Move & move, const Board &board)
{
	Board   B(board);
	B.commitMove(move);
	return B;
}

const char &Board::getLetter(unsigned short row, unsigned short column) const
{
	return m_board[row][column].letter;
}

bool Board::isEmptySquare(unsigned short row, unsigned short column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return m_board[row][column].isEmpty();
	}
	return true;
	//throw EXCEPTION_OUT_OF_BOUND;
}

Board::Board(const Square board[ROWS_COUNT][COLUMNS_COUNT])
{
	try
	{
		LettersOnBoard = "";
		for (size_t i = 0; i < ROWS_COUNT; i++)
			for (size_t j = 0; j < COLUMNS_COUNT; j++)
			{
				m_board[i][j] = board[i][j];
				if (!m_board[i][j].isEmpty())
					LettersOnBoard += m_board[i][j].letter;
			}
	}
	catch (...)
	{
		//throw "error in board init";
	}
}

Board::Board(char board[15][15])
{
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			m_board[i][j].letter = board[i][j];
		}
	}
}

bool Board::isMoveValid(const Move &oponentMove, GaddagNode* root, std::string word) {
	bool hasAnchor = false;
	int i, ilen;
	for (i = 0, ilen = oponentMove.Plays.size(); i < ilen; ++i) {
		if (!isEmptySquare(oponentMove.Plays[i].coordinates.second, oponentMove.Plays[i].coordinates.first))
			return false;
		else if (isAnchor(oponentMove.Plays[i].coordinates.second, oponentMove.Plays[i].coordinates.first)) {
			hasAnchor = true;
			if (!checkCharInHorizontalSet(oponentMove.Plays[i].coordinates.second, oponentMove.Plays[i].coordinates.first, oponentMove.Plays[i].Letter)
				|| !checkCharInVerticalSet(oponentMove.Plays[i].coordinates.second, oponentMove.Plays[i].coordinates.first, oponentMove.Plays[i].Letter))
				return false;
		}
	}


	return (hasAnchor && root->contains(word));
}

bool Board::checkMoveHorizontal(const Move& move) {
	if (move.Plays.size() == 1) {
		if (!isEmptySquare(move.Plays[0].coordinates.second, move.Plays[0].coordinates.first - 1) ||
			!isEmptySquare(move.Plays[0].coordinates.second, move.Plays[0].coordinates.first + 1))
			return true;
		else
			return false;
	}
	if (move.Plays[0].coordinates.second == move.Plays[1].coordinates.second) // if y = y
		return true;
	else
		return false;
}

void Board::formatMyMove(const Move& move, playMove & moveToBeSent) {
	if (checkMoveHorizontal(move)) {
		moveToBeSent.direction = 0;
		/// sort the vector of plays inside the move according to plays[i].coordinates.first not implemented   hena first
	}
	else
	{
		moveToBeSent.direction = 1;
		/// sort the vector of plays inside the move according to plays[i].coordinates.second not implemented   hena second		
	}
	moveToBeSent.Scolumn = move.Plays[0].coordinates.first; /// x
	moveToBeSent.Srow = move.Plays[0].coordinates.second;  /// y 
	int i, ilen;
	for (i = 0, ilen < move.Plays.size(); i < ilen; ++i) {
		moveToBeSent.tiles.push_back(move.Plays[i].Letter);
	}
}

std::string Board::formatOponentMove(const player2Move_formated& move, int& challengeTime, uTime& currentTime, Move &oponentMove, double& score) {
	string word = "";
	if (move.direction == 0) { // if horizontal
		int y = move.Srow;
		int prev = move.Scolumn - 1;
		while (!isEmptySquare(y, prev)) {
			word.insert(0, 1, this->m_board[y][prev].letter);
			prev--;
		}
		int i, ilen;
		int next = move.Scolumn;
		for (i = 0, ilen = move.tiles.size(); i < ilen; ++i) {
			while (!isEmptySquare(y, next)) {
				word += this->m_board[y][next].letter;
				next++;
			}
			word += move.tiles[i];
			if(move.blankIndecies[0] == i || move.blankIndecies[1] == i)
				oponentMove.addPlay(next, y, move.tiles[i],true);
			else
				oponentMove.addPlay(next, y, move.tiles[i]);
		}
	}
	else {
		int x = move.Scolumn;
		int prev = move.Srow - 1;
		while (!isEmptySquare(prev, x)) {
			word.insert(0, 1, this->m_board[prev][x].letter);
			prev--;
		}
		int i, ilen;
		int next = move.Srow;
		for (i = 0, ilen = move.tiles.size(); i < ilen; ++i) {
			while (!isEmptySquare(next, x)) {
				word += this->m_board[next][x].letter;
				next++;
			}
			word += move.tiles[i];
			if (move.blankIndecies[0] == i || move.blankIndecies[1] == i)
				oponentMove.addPlay(x, next, move.tiles[i], true);
			else
				oponentMove.addPlay(x, next, move.tiles[i]);
		}
	}
	challengeTime = move.challengeTime;
	currentTime = move.time;
	score = (double)move.score;
	return word;

}

Board::Board()
{
	for (size_t i = 0; i < ROWS_COUNT; i++)
		for (size_t j = 0; j < COLUMNS_COUNT; j++)
		{
			m_board[i][j] = Board::BoardForm[i][j];
		}
	LettersOnBoard = "";
}

Board::Board(const Board&b) {

	std::copy(&b.m_board[0][0], &b.m_board[0][0] + ROWS_COUNT * COLUMNS_COUNT, &m_board[0][0]);
	/*	for (size_t i = 0; i < ROWS_COUNT; i++)
			for (size_t j = 0; j < COLUMNS_COUNT; j++)
			{
				m_board[i][j] = b.m_board[i][j];
				if (!m_board[i][j].isEmpty())
					LettersOnBoard+=m_board[i][j].letter;
			}
			*/
}

void Board::setTile(char letter, unsigned short row, unsigned short column)
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		m_board[row][column].letter = letter;
		return;
	}
	//throw EXCEPTION_OUT_OF_BOUND;
}

bool Board::isHook(unsigned short row, unsigned short column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return !m_board[row][column].isEmpty() ||
			((column < COLUMNS_COUNT - 1) && m_board[row][column + 1].isEmpty()) || // right
			((column > 0) && m_board[row][column - 1].isEmpty()) ||				   // left
			((row > 0) && m_board[row - 1][column].isEmpty()) ||					   // top
			((column < ROWS_COUNT - 1) && m_board[row + 1][column].isEmpty())	   // down
			;
	}
	//throw EXCEPTION_OUT_OF_BOUND;
}

bool Board::isAnchor(unsigned short row, unsigned short column) const
{
	if (row == 7 && column == 7 && m_board[row][column].isEmpty()) {
		return true;
	}
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return m_board[row][column].isEmpty() &&
			(
			((column < COLUMNS_COUNT - 1) && !m_board[row][column + 1].isEmpty()) || // right
				((column > 0) && !m_board[row][column - 1].isEmpty()) ||						// left
				((row > 0) && !m_board[row - 1][column].isEmpty()) ||						// top
				((row < ROWS_COUNT - 1) && !m_board[row + 1][column].isEmpty())				// down
				);
	}
	//throw EXCEPTION_OUT_OF_BOUND;
	return false;
}

void Board::computeCrossSets(GaddagNode* g) {

	for (int j = 0; j < COLUMNS_COUNT; j++) {
		for (int i = 0; i < ROWS_COUNT; i++) {
			if (isAnchor(i, j)) {
				if (!isEmptySquare(i + 1, j) || !isEmptySquare(i - 1, j)) {
					m_board[i][j].verticalSet.clear();
					computeVerticalSet(i, j, g);
				}
				if (!isEmptySquare(i, j + 1) || !isEmptySquare(i, j - 1)) {
					m_board[i][j].horizontalSet.clear();
					computeHorizontalSet(i, j, g);
				}
			}
		}
	}
}

void Board::computeVerticalSet(int i, int j, GaddagNode* root) {
	GaddagNode* current = root;
	//if it has a tile both side up and down
	if (!isEmptySquare(i - 1, j) && !isEmptySquare(i + 1, j)) {
		int y = i - 1;
		while (!isEmptySquare(y, j)) {

			current = current->getChildren(getLetter(y, j));
			if (current == NULL) {
				return;
			}
			y--;
		}
		//start making suffix
		current = current->getChildren('[');
		if (current != NULL) {
			GaddagNode* base = current;
			int k;
			for (k = 0; k < 26; ++k) {
				current = base;
				current = current->getChildren(mapping[k]);
				y = i + 1;
				while (current != NULL && !isEmptySquare(y + 1, j)) {	//while there is a letter down and haven't reached a null node
					current = current->getChildren(getLetter(y, j));
					y++;
				}
				if (current != NULL) {
					if (current->hasCharAsEnd(getLetter(y, j))) {
						m_board[i][j].verticalSet.insert(mapping[k]);
					}
				}
			}
		}
		//else if it has a tile up 
	}
	else if (!isEmptySquare(i - 1, j)) {
		int y = i - 1;
		while (!isEmptySquare(y, j)) {
			current = current->getChildren(getLetter(y, j));
			if (current == NULL) {
				return;
			}
			y--;
		}
		current = current->getChildren('[');
		//if we can switch to making a suffix
		if (current != NULL) {
			std::vector<unsigned int> positions;
			current->getOnesPositions(current->end, positions);
			int iter, ilen;
			for (iter = 0, ilen = positions.size(); iter < ilen; ++iter) {
				m_board[i][j].verticalSet.insert(mapping[positions[iter]]);
			}
		}
		//else if it has a tile down
	}
	else if (!isEmptySquare(i + 1, j)) {
		int y = i + 1;
		//go to right most tile
		while (!isEmptySquare(y + 1, j)) {
			y++;
		}
		while (y > i) {
			current = current->getChildren(getLetter(y, j));
			if (current == NULL) {
				return;
			}
			y--;
		}
		std::vector<unsigned int> positions;
		current->getOnesPositions(current->end, positions);
		int iter, ilen;
		for (iter = 0, ilen = positions.size(); iter < ilen; ++iter) {
			m_board[i][j].verticalSet.insert(mapping[positions[iter]]);
		}
	}
}

void Board::computeHorizontalSet(int i, int j, GaddagNode* root) {
	GaddagNode* current = root;
	//if it has a tile both side
	if (!isEmptySquare(i, j - 1) && !isEmptySquare(i, j + 1)) {
		int x = j - 1;
		while (!isEmptySquare(i, x)) {
			current = current->getChildren(getLetter(i, x));
			if (current == NULL) {
				return;
			}
			x--;
		}
		current = current->getChildren('[');
		if (current != NULL) {
			GaddagNode* base = current;
			int k;
			for (k = 0; k < 26; ++k) {
				current = base;
				current = current->getChildren(mapping[k]);
				x = j + 1;
				while (current != NULL && !isEmptySquare(i, x + 1)) {
					current = current->getChildren(getLetter(i, x));
					x++;
				}
				if (current != NULL) {
					if (current->hasCharAsEnd(getLetter(i, x))) {
						m_board[i][j].horizontalSet.insert(mapping[k]);
					}
				}
			}

		}
		//else if it has a tile left
	}
	else if (!isEmptySquare(i, j - 1)) {
		int x = j - 1;
		while (!isEmptySquare(i, x)) {
			current = current->getChildren(getLetter(i, x));
			if (current == NULL) {
				return;
			}
			x--;
		}
		current = current->getChildren('[');
		//if we can switch to making a suffix??
		if (current != NULL) {
			std::vector<unsigned int> positions;
			current->getOnesPositions(current->end, positions);
			int iter, ilen;
			for (iter = 0, ilen = positions.size(); iter < ilen; ++iter) {
				m_board[i][j].horizontalSet.insert(mapping[positions[iter]]);
			}
		}
		//else if it has a tile to the right
	}
	else if (!isEmptySquare(i, j + 1)) {
		int x = j + 1;
		//go to the end of this word
		while (!isEmptySquare(i, x + 1)) {
			x++;
		}
		while (x > j) {
			current = current->getChildren(getLetter(i, x));
			if (current == NULL) {
				return;
			}
			x--;
		}
		std::vector<unsigned int> positions;
		current->getOnesPositions(current->end, positions);
		int iter, ilen;
		for (iter = 0, ilen = positions.size(); iter < ilen; ++iter) {
			m_board[i][j].horizontalSet.insert(mapping[positions[iter]]);
		}
	}
}

bool Board::checkCharInHorizontalSet(int i, int j, char l) const {

	if (m_board[i][j].horizontalSet.find(l) != m_board[i][j].horizontalSet.end())
	{
		return true;
	}
	return false;

}

bool Board::checkCharInVerticalSet(int i, int j, char l) const {
	if (m_board[i][j].verticalSet.find(l) != m_board[i][j].verticalSet.end())
	{
		return true;
	}
	return false;
}

Board::~Board()
{
}