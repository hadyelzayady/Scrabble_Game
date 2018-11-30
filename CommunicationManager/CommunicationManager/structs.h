#pragma once
#include <cstdint>
#include <vector>
struct readyStruct
{
	
	uint8_t type;
	uint8_t order;
	std::vector<uint8_t> tiles;
	std::vector<uint8_t>board;
	int32_t score;
	int32_t opponentScore;
	int32_t playerTime;
	int32_t totalTime;
};

struct readyStruct_formated
{
    int type;
	int order;
	std::vector<char> tiles;
	char board[15][15];
	int score;
	int opponentScore;
	int playerTime;
	int totalTime;
};