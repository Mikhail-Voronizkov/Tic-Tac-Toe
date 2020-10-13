#include "Player.h"

Player::Player()
{
	name = "Defualt_Player";
	symbol = "";
}

Player::Player(string name, string symbol)
{
	this->name = name;
	this->symbol = symbol;
}

void Player::setName(string name)
{
	this->name = name;
}

void Player::setSymbol(string symbol)
{
	this->symbol = symbol;
}

string Player::getName()
{
	return name;
}

string Player::getSymbol()
{
	return symbol;
}
