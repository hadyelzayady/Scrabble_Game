#include <iostream>
#include "GameManager.h"
#include "Gaddag.h"
#include "EndSimulation.h"
#include <fstream>
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
	board.commitMove(best);
	writeBoardToFile(board);
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