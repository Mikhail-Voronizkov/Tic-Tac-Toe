#pragma once
#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<string>> matrix2D;

class Board
{
public:
	Board();
	Board(int width, int height, string initValue);
	void resizeBoard(int width, int height);
	int getHeight();
	int getWidth();
	void drawBoard();
	friend class Game;
	

private:
	matrix2D matrix;
	int width;
	int height;
};

