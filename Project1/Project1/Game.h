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
	Player* checkHorizontal(int first_dimensional, int second_dimensional);
	Player* checkVertical(int first_dimensional, int second_dimensional);
	Player* checkDiagonal(int first_dimensional, int second_dimensional);

	int available_winning_move(Player& player);
	bool check_Horizontal_Line(int first_dimensional, int second_dimensional, int lenght, string symbol);
	bool check_Vertical_Line(int first_dimensional, int second_dimensional, int lenght, string symbol);
	bool check_Diagonal_Line(int first_dimensional, int second_dimensional, int lenght, string symbol);

	void draw();

private:
	Board board;
	string initValue;
	int available;
	Player player[2];
	Player* currentPlayer;
	std::map<string, int> scoreTable;
};

