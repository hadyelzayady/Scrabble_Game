#include <iostream>
#include "GameManager.h"
using namespace std;

int main()
{
	string * playerNames;
	int playerCount = 2;
	playerNames = new string[playerCount];
	playerNames[0] = "Scrabby-Do";
	playerNames[1] = "Enemy";
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