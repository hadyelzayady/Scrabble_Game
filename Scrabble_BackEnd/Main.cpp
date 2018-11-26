#include <iostream>
#include "GameManager.h"
using namespace std;

int main()
{
	////(test commitmove and commitMoveSim
	Board board;
	Move move;
	Play play;
	play.set_Letter('A');
	play.set_Coordinates(pair<int, int>(7, 6));
	move.addPlay(play);
	Board b= board.commitMoveSim(move);
	play.set_Letter('Z');
	move.addPlay(play);
	board.commitMove(move);
	//////////
	string *playerNames;
	int playerCount = 2;
	playerNames = new string[playerCount];
	playerNames[0] = "Scrabby-Do";
	playerNames[1] = "Enemy";
	/*
	Intiating  instance tileLookUp from TileLookUp class
	*/
	TileLookUp *tileLookUp = new TileLookUp();
	GameManager *gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	gameManager->simulateGame();
	system("pause");
	return 0;
}