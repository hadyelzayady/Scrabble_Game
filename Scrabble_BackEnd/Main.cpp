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
	board.LettersOnBoard = "";
	if (myfile.is_open())
	{
		for (size_t i = 0; i < 15; i++)
		{
			getline(myfile, line);
			for (size_t j = 0; j < 15; j++)
			{
				if (line[j] != '*')
				{
					board.m_board[i][j].letter = line[j];
					board.LettersOnBoard += line[j];
				}
				
			}
		}
		myfile.close();
	}
	return board;
}
void  writeBoardToFile(const Board&board)
{
	std::ofstream myfile;

	myfile.open("board_status2.txt", std::ios_base::app);
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
void clearfile()
{
	std::ofstream myfile;

	myfile.open("board_status2.txt", 'w');
	myfile << "";
}
int main()
{

	Gaddag* g = new Gaddag("SOWPODS.txt");
	Board board = parsefile();
	clearfile();
	writeBoardToFile(board);
	board.computeCrossSets(g->root);
	Rack myrack, oprack;
	myrack.addTile('Q');
	myrack.addTile('N');
	myrack.addTile('A');
	myrack.addTile('K');
	myrack.addTile('C');
	myrack.addTile('Z');

	oprack.addTile('Q');
	oprack.addTile('U');
	oprack.addTile('G');
	oprack.addTile('H');
	oprack.addTile('J');
	oprack.addTile('Z');

	TileLookUp tl;
	Heuristics hr;

	EndSimulation ends(&board, &tl, oprack, myrack, g, &hr);

	while (!oprack.getRackTiles().empty() && !myrack.getRackTiles().empty())
	{
		EndSimulation ends(&board, &tl, oprack, myrack, g, &hr);

		Move best = ends.start();
		if (best.Plays.size() != 0)
		{
			cout << "score "<<ScoreManager::calculateScore(best, &board, &tl)<<endl;
			board.commitMove(best);
			board.computeCrossSets(g->root);
			writeBoardToFile(board);
			myrack.commitMove(&best);
			cout << best.Plays[0].coordinates.first << "," << best.Plays[0].coordinates.second << endl;
		}
		else
			cout << "pass\n";
		//opposite game
		Rack temp = oprack;
		oprack=myrack;
		myrack = temp;
		cout << "end simulation\n";

	}



	system("pause");
	return 0;
} 

