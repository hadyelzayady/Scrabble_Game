#include <iostream>
#include "GameManager.h"
#include "Gaddag.h"
#include "EndSimulation.h"
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
int main()
{

	Gaddag* g = new Gaddag("sowpods.txt");
	Board board = parsefile();
	Rack myrack, oprack;
	myrack.addTile('E');
	myrack.addTile('N');
	myrack.addTile('R');
	myrack.addTile('T');

	oprack.addTile('B');
	oprack.addTile('O');
	oprack.addTile('U');
	oprack.addTile('W');
	TileLookUp tl;
	Heuristics hr;
	EndSimulation ends(board, &tl, oprack, myrack, g, &hr);
	Move best=ends.start();
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