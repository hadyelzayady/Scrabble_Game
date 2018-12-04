#include <iostream>
#include "GameManager.h"
using namespace std;

int main()
{
	string * playerNames;
	int playerCount = 2;

	cout << " we have started to search" << endl;
	playerNames = new string[playerCount];
	playerNames[0] = "Scrabby-Do";
	playerNames[1] = "Enemy";
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
	Board V = Board::commitMoveSim(*z, *B);*/
	Square list[15][15];
	list[7][4].letter = 'L';
	list[7][5].letter = 'A';
	list[7][7].letter = 'C';
	list[7][8].letter = 'I';
	list[7][9].letter = 'S';
	list[7][10].letter = 'E';
	
	

	Board b(list);
	Rack  *rack = new Rack();
	rack->addTile('I');

	ProbabilityManager * Pm = new ProbabilityManager();
	TileLookUp * TL = new TileLookUp();
	Gaddag *g = new Gaddag("../Text/SOWPODS.txt");
	PreEndGameManager * PreEndManager = new PreEndGameManager(TL,g);
	vector <Move> MoveList = g->findWords(rack->getRackTiles(),b);

	Move * M = &PreEndManager->Blocking(MoveList,rack,b,Pm);
//	cout << (M->Plays.begin())->Letter << endl;
//	MonteCarlo * M = new MonteCarlo(r,c,Pm);
	// M->simulation(100);
//	 Utilities * u =new  Utilities();
/*
	Intiating  instance tileLookUp from TileLookUp class
	*/
	//TileLookUp * tileLookUp = new TileLookUp();
	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	//gameManager->simulateGame();
	cout << "finished" << endl;
	system("pause");
	return 0;
} 