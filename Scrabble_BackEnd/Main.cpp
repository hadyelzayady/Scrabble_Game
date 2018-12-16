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
	myrack.addTile('A');
	myrack.addTile('Q');
	myrack.addTile('A');
	myrack.addTile('H');

	oprack.addTile('A');
	oprack.addTile('U');
	oprack.addTile('G');
	oprack.addTile('H');
	oprack.addTile('E');
	oprack.addTile('Z');

	TileLookUp tl;
	Heuristics hr;
	Logger log;
	log.DisplayBoard(&board);
	bool h = true;
	EndSimulation ends(&board, &tl, oprack, myrack, g, &hr);
	vector<Move> moves;
	g->findWords(myrack.getRackTiles(), moves, &board);

	for (size_t i = 0; i < moves.size(); i++)
	{
		log.PrintMove(&moves[i]);
	}
	while (!ends.opponetRack.getRackTiles().empty() && !ends.myRack.getRackTiles().empty())
	{
		Move best = ends.start();
		if (best.Plays.empty())
		{
			if (h == true)
				break;
			h = true;
		}
		else
			h = false;
			
		if (best.Plays.size() != 0)
		{
			//cout << "score "<<ScoreManager::calculateScore(best, &board, &tl)<<endl;
			board.commitMove(best);
			log.DisplayRack(&ends.myRack);
			log.DisplayRack(&ends.opponetRack);

			log.DisplayBoard(&board);
			ends.myRack.commitMove(&best);
			log.DisplayRack(&ends.myRack);
			log.DisplayRack(&ends.opponetRack);
			board.computeCrossSets(g->root);
			writeBoardToFile(board);
			cout << best.Plays[0].coordinates.first << "," << best.Plays[0].coordinates.second << endl;
		}
		//else
		//	cout << "pass\n";
		//opposite game
		Rack temp = ends.opponetRack;
		ends.opponetRack=ends.myRack;
		ends.myRack= temp;


		//cout << "end simulation\n";

	}



	system("pause");
	return 0;
} 

