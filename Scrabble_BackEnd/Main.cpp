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
	/*
	Intiating  instance tileLookUp from TileLookUp class
	*/
	TileLookUp * tileLookUp = new TileLookUp();
	GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	gameManager->simulateGame();
	system("pause");
	return 0;
} 