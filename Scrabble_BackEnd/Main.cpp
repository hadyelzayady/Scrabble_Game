#include <iostream>
#include "GameManager.h"
#include <fstream>
#include <iostream>
#include <string>
#include "EndSimulation.h"
#include "ScoreManager.h"
using namespace std;
Move createMove(string line,bool h) {
	cout << line;
	char* word = strtok(&line[0], " ");
	char* row = strtok(&line[strlen(word) + 1], " ");
	char* col= strtok(&line[strlen(word)+strlen(row)+2], " ");
	Move move;
	//stoi does not work propery
	// opponent moves are vertical
	if (h) {
		for (size_t i = 0; i < strlen(word); i++)
		{
			int r = atoi(row);
			int c = atoi(col);
			Play play(r, c + i, word[i], false);
			move.addPlay(play);
		}
	}
	else {
		for (size_t i = 0; i < strlen(word); i++)
		{
			int r = atoi(row);
			int c = atoi(col);
			Play play(r+i,c, word[i], false);
			move.addPlay(play);
		}
	}

	return  move;
}
Board parsefile(vector<Move>& mymoves, vector<Move>& opmoves)
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
					if(line[j] != '*')
						board.m_board[i][j].letter = line[j];
				}
			}
			for (size_t i = 0; i < 6; i++)
			{
				getline(myfile, line);
				Move move=createMove(line,true);
				mymoves.push_back(move);
			}
			for (size_t i = 0; i < 3; i++)
			{
				getline(myfile, line);
				Move move = createMove(line,false);
				opmoves.push_back(move);
			}
			myfile.close();

	}

	return board;

}
int main()
{
	////(test commitmove and commitMoveSim
	//Board board;
	//Move move;
	//Play play;
	//play.set_Letter('A', 1);
	//play.set_Coordinates(pair<int, int>(7, 6));
	//move.addPlay(play);
	//Board b = board.commitMoveSimB(move);
	//play.set_Letter('Z', 1);
	//move.addPlay(play);
	//board.commitMove(move);
	//////////
	//vector<Move> mymoves,opmoves;
	//Board board = parsefile(mymoves,opmoves);
	//TileLookUp til;
	//ScoreManager sc(&board,&til);
	//Rack myrack("ENDWISE"), oprack("BOUWKAF");
	//EndSimulation end(board,&sc,oprack,myrack,opmoves,mymoves);
	//pair<int,Move> bestmove=end.start();
	//////
	char x = '\0o';
	string y = "hell";
	y+='o';
	x = 'c';

	//////
	//string *playerNames;
	//int playerCount = 2;
	//playerNames = new string[playerCount];
	//playerNames[0] = "Scrabby-Do";
	//playerNames[1] = "Enemy";
	//Rack *r = new Rack();
	//r->addTile('A');
	//r->addTile('N');
	//r->addTile('B');
	//r->addTile('S');
	//r->addTile('D');
	//r->addTile('E');
	//r->addTile('F');
	//char c[] = {'G', 'Z', 'Y', 'X'};
	//ProbabilityManager *Pm = new ProbabilityManager();
	//MonteCarlo *M = new MonteCarlo(r, c, Pm);
	//M->simulation(100);
	//Utilities *u = new Utilities();
	///*
	// Intiating  instance tileLookUp from TileLookUp class
	// */
	//TileLookUp * tileLookUp = new TileLookUp();
	//GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	//gameManager->simulateGame();
	system("pause");
	return 0;
}