#include "Board.h"
Square Board::BoardForm[ROWS_COUNT][COLUMNS_COUNT] = { {Square(WordBonusX3),Square(NoBonus),Square(NoBonus),
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
	{Square(NoBonus),Square(NoBonus),Square(LetterBonusX2),
		Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX2),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX2),Square(NoBonus),Square(NoBonus)},
	{Square(NoBonus),Square(LetterBonusX3),Square(NoBonus),
		Square(NoBonus),Square(NoBonus),Square(LetterBonusX3)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX3),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(LetterBonusX3),Square(NoBonus)},
	{Square(NoBonus),Square(NoBonus),Square(NoBonus),
		Square(NoBonus),Square(WordBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)},
	{Square(LetterBonusX2),Square(NoBonus),Square(NoBonus),
		Square(WordBonusX2),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(LetterBonusX2),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(WordBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX2)},
	{Square(NoBonus),Square(NoBonus),Square(WordBonusX2),
		Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX2),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(WordBonusX2),Square(NoBonus),Square(NoBonus)}
	,{Square(NoBonus),Square(WordBonusX2),Square(NoBonus),
		Square(NoBonus),Square(NoBonus),Square(LetterBonusX3)
		,Square(NoBonus),Square(NoBonus),Square(NoBonus)
		,Square(LetterBonusX3),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX2),Square(NoBonus)},
		{Square(WordBonusX3),Square(NoBonus),Square(NoBonus),
		Square(LetterBonusX2),Square(NoBonus),Square(NoBonus)
		,Square(NoBonus),Square(WordBonusX3),Square(NoBonus)
		,Square(NoBonus),Square(NoBonus),Square(LetterBonusX2)
		,Square(NoBonus),Square(NoBonus),Square(WordBonusX3)} };
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
		LettersOnBoard+=letter;
	}
}
void Board::commitMoves(const vector<Move> &moves)
{
	for (Move move : moves) 
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
}
//?we use commitMoveSim instead of commitMove as we return new board with move changes and no effect happens to the original board
Board Board::commitMoveSimB(const Move &move)
{
	Board newBoard(m_board);
	newBoard.commitMove(move);
	return newBoard; //? still not sure if we should return 2d array or board object but soliman needs board object to get moves
}
void Board::commitMoveSimC(const Move & move, Board & newBoard)
{
	newBoard.commitMove(move);
}
void Board::UnCommitMove(const Move & move)
{
	//
	vector<Play>plays = move.Plays;
	string moveLetters="";//2 approachs ,find substring of move in boardletters string then remove it or remove one letter one by one in for loop 
	for (size_t i = 0; i < plays.size(); i++)
	{
		pair<int, int> position = plays[i].get_Coordinates();
		removeTile(position.second, position.first);
		moveLetters += plays[i].get_Letter();//TODO: remove move letters from board
	}
	
}
Board Board::commitMoveSim(const Move & move, Board board)
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
	return false;
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
					LettersOnBoard+=m_board[i][j].letter;
			}
	}
	catch (...)
	{
		throw "error in board init";

	}
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
	for (size_t i = 0; i < ROWS_COUNT; i++)
		for (size_t j = 0; j < COLUMNS_COUNT; j++)
		{
			m_board[i][j] = b.m_board[i][j];
			if (!m_board[i][j].isEmpty())
				LettersOnBoard+=m_board[i][j].letter;
		}
}


void Board::setTile(char letter, unsigned short row, unsigned short column)
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		m_board[row][column].letter = letter;
		return;
	}

	throw EXCEPTION_OUT_OF_BOUND;

}
void Board::removeTile(unsigned short row, unsigned short column)
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		m_board[row][column].letter = EMPTY_SQUARE;
		return;
	}

	throw EXCEPTION_OUT_OF_BOUND;

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

	throw EXCEPTION_OUT_OF_BOUND;
}
 bool Board::isAnchor(unsigned short row, unsigned short column) const
{
	if (row < ROWS_COUNT && column < COLUMNS_COUNT)
	{
		return m_board[row][column].isEmpty() &&
			((column < COLUMNS_COUNT - 1) && !m_board[row][column + 1].isEmpty()) || // right
			((column > 0) && !m_board[row][column - 1].isEmpty()) ||						// left
			((row > 0) && !m_board[row - 1][column].isEmpty()) ||						// top
			((row < ROWS_COUNT - 1) && !m_board[row + 1][column].isEmpty())				// down
			;
	}
	throw EXCEPTION_OUT_OF_BOUND;
}

Board::~Board()
{
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
				 current = current->getChildren(mapping[i]);
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
				 current = current->getChildren(mapping[i]);
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
				 m_board[i][j].verticalSet.insert(mapping[positions[iter]]);
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
			 m_board[i][j].verticalSet.insert(mapping[positions[iter]]);

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


