#pragma once
#include "Board.h"
#include "Rack.h"
#include "TileLookUp.h"
#include "ScoreManager.h"
class AI
{
public:

	// change return type to Move object after it is added
	void makeDecision(Rack*, Board*, ScoreManager*, TileLookUp*);
	AI();
	~AI();
};

