#include "Player.h"

Player::Player(string name)
{
	playerName = name;
	playerScore = 0;
	rack = new Rack;
}
Player:: ~Player()
{
	delete rack;
}
string Player::getPlayerName()
{
	return playerName;
}

Rack & Player::getRack()
{
	return *rack;

}