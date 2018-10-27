#include <iostream>
#include "GameManager.h"
using namespace std;

int main(int argc, char *argv[])
{
	string * playerNames;
	int playerCount = atoi(argv[1]);
	playerNames = new string[playerCount];
	for (int i = 0; i < playerCount; i++) {
		playerNames[i] = argv[i + 2];
		// cout << playerNames[i] << endl;
	}
	/*
	Intiating  instance tileLookUp from TileLookUp class
	*/
	TileLookUp * tileLookUp = new TileLookUp();
	GameManager * gameManager = new GameManager(tileLookUp, playerCount, playerNames);
	gameManager->simulateGame();
	system("pause");
	return 0;
} 