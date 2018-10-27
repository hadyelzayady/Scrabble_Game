#include "GameManager.h"


void GameManager::simulateGame() {

}

GameManager::GameManager(TileLookUp* tileLookUp, int playerCount, string playerNames[])
{
	cout << "Game Manager Initialising Components..." << endl;
	// Capture the parameters
	this->tileLookup = tileLookUp;
	this->playerCount = playerCount;

	// Initialise the board and score manager
	boardManager = new Board();
	scoreManager = new ScoreManager(boardManager, tileLookUp);

	// Allocate a space for every player
	players = new Player*[playerCount];

	// Initialise players with names
	for (int i = 0; i < playerCount; i++)
		players[i] = new Player(playerNames[i]);
}


GameManager::~GameManager()
{
	delete boardManager;
	for (int i = 0; i < playerCount; i++)
		delete players[i];
	delete players;
}
