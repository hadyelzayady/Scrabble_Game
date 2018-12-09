#include <iostream>
#include "GameManager.h"
#include "Logger.h"
using namespace std;

int main()
{
	string * playerNames;
	int playerCount = 2;

	cout << " Welcome to Scrabby-Doo " << endl;
	playerNames = new string[playerCount];
	playerNames[0] = "Player";
	playerNames[1] = "Enemy";

	Player ** players = new Player*[playerCount];

	for (int i = 0; i < playerCount; i++) {
		players[i] = new Player(playerNames[i]);
	}
	/*
	Rack* r = new Rack();
	r->addTile('A');
	r->addTile('N');
	r->addTile('B');
	r->addTile('S');
	r->addTile('D');
	r->addTile('E');
	r->addTile('F');
	char c[] = { 'G','Z','Y','X' };
	ProbabilityManager * Pm = new ProbabilityManager();
	Board *B = new Board();
	Move* M = new Move();
	Play *P = new Play();
	P->set_Coordinates(make_pair(2, 3));
	P->set_Letter('A', 1);
	M->addPlay(*P);
	B->commitMove(*M);
	P->set_Coordinates(make_pair(4,5));
	P->set_Letter('Z', 2);
	Move* z = new Move();
	z->addPlay(*P);
	Board V = Board::commitMoveSim(*z, *B);
	/*Square list[15][15];
	list[7][4].letter = 'L';
	list[7][5].letter = 'A';
	list[7][7].letter = 'C';
	list[7][8].letter = 'I';
	list[7][9].letter = 'S';
	list[7][10].letter = 'E';
	//Rack  *rack = new Rack();
	//rack->addTile('I');
	//ProbabilityManager * Pm = new ProbabilityManager();*/


	cout << "Initialising TileLookup...";
	TileLookUp * TL = new TileLookUp();
	cout << "Done" << endl;


	cout << "Building GADDAG..." << endl;
	Gaddag *g = new Gaddag("../Text/SOWPODS.txt");
	cout << "Done" << endl;


	cout << "Initialising Board and Bag..." << endl;
	Board * b = new Board();
	b->computeCrossSets(g->root);
	BagOfLetters * bag = new BagOfLetters();
	cout << "Done" << endl;


	cout << "Distributing Racks..." << endl;


	for (int i = 0; i < playerCount; i++) {
		players[i]->rack = new Rack();
		//players[i]->rack->addTile('[');
		while (players[i]->rack->list.size() < RACK_SIZE) {
			players[i]->rack->addTile(bag->draw());
		}
	}
	cout << "Done" << endl;

	MidGameManager * midMan = new MidGameManager(TL, g);
	Logger logger;

	int turn = 0;
	while (1) {
		logger.DisplayRack(players[1]->rack);
		logger.DisplayBoard(b);
		logger.DisplayRack(players[0]->rack);
		int playerTurn = turn % playerCount;
		vector <Move> MoveList;
		g->findWords(players[playerTurn]->rack->getRackTiles(), MoveList, b);
		int selectedMoveIndex = midMan->getBestMove(turn == 0, MoveList, players[playerTurn]->rack, b);
		cout << "Move Chosen: ";
		logger.PrintMove(&MoveList[selectedMoveIndex]);
		b->commitMove(MoveList[selectedMoveIndex]);
		players[playerTurn]->rack->commitMove(&MoveList[selectedMoveIndex]);
		while (players[playerTurn]->rack->list.size() < RACK_SIZE) {
			players[playerTurn]->rack->addTile(bag->draw());
		}

		//Board * b = new Board();
		//b->m_board[7][7].letter = 'H';
		//b->m_board[8][7].letter = 'U';
		//b->m_board[9][7].letter = 'B';
		//b->m_board[10][7].letter = 'B';
		//b->m_board[11][7].letter = 'L';
		//b->m_board[12][7].letter = 'Y';
		//b->m_board[9][4].letter = 'Z';
		//b->m_board[9][5].letter = 'A';
		//b->m_board[9][6].letter = 'M';
		//b->m_board[9][8].letter = 'U';
		//b->m_board[9][9].letter = 'K';

		//std::vector<char> rack;
		//rack.push_back('G');
		//rack.push_back('A');
		//rack.push_back('L');
		//rack.push_back('A');
		//rack.push_back('I');
		//rack.push_back('Y');
		//rack.push_back('A');

		//b->computeCrossSets(g->root);
		//std::vector<Move> movestest = g->findWords(rack, b);

		turn++;
		system("pause");
	}

/*	//	cout << (M->Plays.begin())->Letter << endl;

	//	MonteCarlo * M = new MonteCarlo(r,c,Pm);
	// M->simulation(100);

	//	 Utilities * u =new  Utilities();

	Intiating  instance tileLookUp from TileLookUp class

	//TileLookUp * tileLookUp = new TileLookUp();
	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	//gameManager->simulateGame();
	cout << "finished" << endl;*/
		system("pause");
		return 0;
	}