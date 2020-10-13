#pragma once
#include<iostream>
using namespace std;

class Player
{
public:
	Player();
	Player(string name, string symbol);
	void setName(string name);
	void setSymbol(string symbol);
	string getName();
	string getSymbol();

private:
	string name;
	string symbol;
};

