#include <iostream>
#include "GameManager.h"
#include "Gaddag.h"
#include "EndSimulation.h"
#include <fstream>
#include "Logger.h"
using namespace std;
Board parsefile()
{
	string line;
	ifstream myfile("board_status.txt");
	Board board;
	if (myfile.is_open())
	{
		for (size_t i = 0; i < 15; i++)
		{
			getline(myfile, line);
			for (size_t j = 0; j < 15; j++)
			{
				if (line[j] != '*')
					board.m_board[i][j].letter = line[j];
			}
		}
		myfile.close();
	}
	return board;
}
//int main()
//{
//	string * playerNames;
//	int playerCount = 2;
//
//	cout << " Welcome to Scrabby-Doo " << endl;
//	playerNames = new string[playerCount];
//	playerNames[0] = "Player";
//	playerNames[1] = "Enemy";
//
//	Player ** players = new Player*[playerCount];
//
//	for (int i = 0; i < playerCount; i++) {
//		players[i] = new Player(playerNames[i]);
//	}
//
//
//	cout << "Initialising TileLookup...";
//	TileLookUp * TL = new TileLookUp();
//	cout << "Done" << endl;
//
//
//	cout << "Building GADDAG..." << endl;
//	Gaddag *g = new Gaddag("../Text/SOWPODS.txt");
//	cout << "Done" << endl;
//
//
//	cout << "Initialising Board and Bag..." << endl;
//	Board * b = new Board();
//	b->computeCrossSets(g->root);
//	BagOfLetters * bag = new BagOfLetters();
//	cout << "Done" << endl;
//
//
//	cout << "Distributing Racks..." << endl;
//
//
//	for (int i = 0; i < playerCount; i++) {
//		players[i]->rack = new Rack();
//		//players[i]->rack->addTile('[');
//		while (players[i]->rack->list.size() < RACK_SIZE) {
//			players[i]->rack->addTile(bag->draw());
//		}
//	}
//	cout << "Done" << endl;
//
//	MidGameManager * midMan = new MidGameManager(TL, g);
//	Logger logger;
//
//	int turn = 0;
//	while (1) {
//		logger.DisplayRack(players[1]->rack);
//		logger.DisplayBoard(b);
//		logger.DisplayRack(players[0]->rack);
//		int playerTurn = turn % playerCount;
//		vector <Move> MoveList = g->findWords(players[playerTurn]->rack->getRackTiles(), b);
//		int selectedMoveIndex = midMan->getBestMove(turn == 0, MoveList, players[playerTurn]->rack, b);
//		cout << "Move Chosen: ";
//		logger.PrintMove(&MoveList[selectedMoveIndex]);
//		b->commitMove(MoveList[selectedMoveIndex]);
//		players[playerTurn]->rack->commitMove(&MoveList[selectedMoveIndex]);
//		while (players[playerTurn]->rack->list.size() < RACK_SIZE) {
//			players[playerTurn]->rack->addTile(bag->draw());
//		}
//
//		//Board * b = new Board();
//		//b->m_board[7][7].letter = 'H';
//		//b->m_board[8][7].letter = 'U';
//		//b->m_board[9][7].letter = 'B';
//		//b->m_board[10][7].letter = 'B';
//		//b->m_board[11][7].letter = 'L';
//		//b->m_board[12][7].letter = 'Y';
//		//b->m_board[9][4].letter = 'Z';
//		//b->m_board[9][5].letter = 'A';
//		//b->m_board[9][6].letter = 'M';
//		//b->m_board[9][8].letter = 'U';
//		//b->m_board[9][9].letter = 'K';
//
//		//std::vector<char> rack;
//		//rack.push_back('G');
//		//rack.push_back('A');
//		//rack.push_back('L');
//		//rack.push_back('A');
//		//rack.push_back('I');
//		//rack.push_back('Y');
//		//rack.push_back('A');
//
//		//b->computeCrossSets(g->root);
//		//std::vector<Move> movestest = g->findWords(rack, b);
//
//		turn++;
//	}
//	system("pause");
//
//}
	/*//	cout << (M->Plays.begin())->Letter << endl;

	//	MonteCarlo * M = new MonteCarlo(r,c,Pm);
	// M->simulation(100);

	return board;
}*/
void  writeBoardToFile(const Board&board)
{
	std::ofstream myfile;

	myfile.open("board_status.txt", std::ios_base::app);
	if (myfile.is_open())
	{
		myfile << "===================================================\n";
		for (size_t i = 0; i < 15; i++)
		{
			string line="";
			for (size_t j = 0; j < 15; j++)
			{
				if (board.m_board[i][j].isEmpty())
					line += "*";
				else
					line += board.m_board[i][j].letter;
			}
			myfile << line<<"\n";
		}
		myfile.close();
	}
}
int main()
{

	Gaddag* g = new Gaddag("SOWPODS.txt");
	Board board = parsefile();
	board.computeCrossSets(g->root);
	Rack myrack, oprack;
	myrack.addTile('E');
	myrack.addTile('N');
	myrack.addTile('R');
	myrack.addTile('A');
	myrack.addTile('B');
	myrack.addTile('C');
	myrack.addTile('D');

	oprack.addTile('B');
	oprack.addTile('Q');
	oprack.addTile('U');
	oprack.addTile('G');
	oprack.addTile('H');
	oprack.addTile('P');
	oprack.addTile('L');

	TileLookUp tl;
	Heuristics hr;

	EndSimulation ends(board, &tl, oprack, myrack, g, &hr);
	Move best=ends.start();
	board.commitMove(best);
	board.computeCrossSets(g->root);

	writeBoardToFile(board);		
	myrack.removeMoveTiles(best);

	EndSimulation ends2(board, &tl, myrack, oprack, g, &hr);
	best = ends2.start();
	board.commitMove(best);
	board.computeCrossSets(g->root);

	writeBoardToFile(board);
	oprack.removeMoveTiles(best);


	EndSimulation ends3(board, &tl, oprack, myrack, g, &hr);
	best = ends3.start();
	board.commitMove(best);
	board.computeCrossSets(g->root);

	writeBoardToFile(board);
	myrack.removeMoveTiles(best);
//	MonteCarlo * M = new MonteCarlo(r,c,Pm);
	// M->simulation(100);
//	 Utilities * u =new  Utilities();
/*
	Intiating  instance tileLookUp from TileLookUp class
	*/
	//TileLookUp * tileLookUp = new TileLookUp();
	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	//gameManager->simulateGame();

	system("pause");
	return 0;
} 