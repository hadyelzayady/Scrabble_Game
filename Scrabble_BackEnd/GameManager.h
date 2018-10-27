#pragma once
#include "TileLookUp.h"
#include "Board.h"
#include "Player.h"
#include "ScoreManager.h"
// FIXME: Remove the comment when the bag class is added
// #include "Bag.h"

class GameManager
{
public:
	// Parameters
	TileLookUp* tileLookup;
	Board * boardManager;
	Player ** players;
	ScoreManager * scoreManager;
	int playerCount;
	// FIXME: Remove the comment when the bag class is added
	// Bag * bagManager;

	// Methods
	void simulateGame();
	GameManager(TileLookUp*, int, string[]);
	~GameManager();
};

