#include "Board.h"


Board::Board()
{
}

Board::Board(int width, int height, string initValue)
{
	resizeBoard(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			matrix[i][j] = initValue;
		}
	}
}

void Board::resizeBoard(int width, int height)
{
	width = (width < 0) ? -width : width;
	height = (height < 0) ? -height : height;

	matrix.resize(height);
	for (int i = 0; i < height; i++) {
		matrix[i].resize(width);
	}

	this->width = width;
	this->height = height;
}

int Board::getHeight()
{
	return height;
}

int Board::getWidth()
{
	return width;
}

void Board::drawBoard()
{	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}
