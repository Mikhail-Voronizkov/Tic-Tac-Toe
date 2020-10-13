#pragma once
#include <map>
#include<iterator>
#include <windows.h>
#include"Board.h"
#include"Player.h"

typedef struct Point {
	int row;
	int col;
};

//Tic Tac Toe game with 2 players
class Game
{
public:
	Game();
	Game(int width, int height, string initValue);
	void run();
	void input();
	void nextTurn();
	int minimax(Board& b, int &alpha, int &beta, int depth, bool isMaximizing);
	Player* checkWinner();
	void draw();

private:
	Board board;
	string initValue;
	int available;
	Player player[2];
	Player* currentPlayer;
	std::map<string, int> scoreTable;
};

