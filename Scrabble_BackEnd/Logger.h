#pragma once
#include"Board.h"
#include<Windows.h>
#include<iostream>
class Logger
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	void DisplayBoard(Square m_board[ROWS_COUNT][COLUMNS_COUNT]);
	Logger();
	~Logger();
};

