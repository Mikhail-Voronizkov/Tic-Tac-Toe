#include "Game.h"



Game::Game()
{
}

Game::Game(int width, int height, string initValue)
{
	//Minimum size is 3 x 3
	width = (width < 3) ? 3 : width;
	height = (height < 3) ? 3 : height;
	this->initValue = initValue;

	board.resizeBoard(width, height);
	for (int i = 0; i < board.getHeight(); i++) {
		for (int j = 0; j < board.getWidth(); j++) {
			board.matrix[i][j] = initValue;
		}
	}
	/*board.matrix[0][2] = "x";
	board.matrix[1][1] = "x";
	board.matrix[2][0] = "x";*/
	available = width * height;

	player[0].setName("Player_1");
	player[0].setSymbol("x");
	player[1].setName("Player_2");
	player[1].setSymbol("o");
	currentPlayer = &player[0];

	scoreTable.insert(pair<string, int>("x", 10));
	scoreTable.insert(pair<string, int>("o", -10));
	scoreTable.insert(pair<string, int>("Tie", 0));
}

void Game::run()
{
	Player* winner = NULL;

	while (winner == NULL) {
		winner = checkWinner();
		if (winner != NULL) {
			cout << endl << ">Result: " << winner->getName() << endl;
			draw();
			break;
		}
		else if (available == 0) {
			cout << endl << ">Result: " << "Tie" << endl;
			draw();
			break;
		}

		cout <<"It's "<< currentPlayer->getName() <<"'s turn" << endl;
		
		//Computer = player[0]
		if (currentPlayer == &player[0] && winner == NULL) {
			nextTurn();
		}
		else if (currentPlayer == &player[1] && winner == NULL) {
			input();
		}

		draw();
	}
	
}

void Game::input()
{
	if (available == 0)
		return;

	int row = 0;
	int col = 0;

	do {
		cout << "------Input---------" << endl;
		cout << "Row: ";
		cin >> row;
		cout << "Col: ";
		cin >> col;
		cout << endl;
	} while (row < 0 || col < 0 || row >= board.getHeight() || col >= board.getWidth() || board.matrix[row][col] != initValue);


	if(board.matrix[row][col] == initValue)
		board.matrix[row][col] = currentPlayer->getSymbol();
	
	currentPlayer = &player[0];
	available--;
}

//Best move for computer
void Game::nextTurn()
{
	if (available == 0)
		return;

	//Computer = Player_1
	int bestScore = 0;
	Point bestMove;
	int alpha = INT_MIN;
	int beta = INT_MAX;
	for (int i = 0; i < board.getHeight(); i++) {
		for (int j = 0; j < board.getWidth(); j++) {
			if (board.matrix[i][j] != initValue)
				continue;
			else if(currentPlayer == &player[0]) {
				board.matrix[i][j] = currentPlayer->getSymbol();
				int score = minimax(board, alpha, beta,0,false);
				board.matrix[i][j] = initValue;
				if (score >= bestScore) {
					bestScore = score;
					bestMove.row = i;
					bestMove.col = j;
				}
			}
		}
	}
	board.matrix[bestMove.row][bestMove.col] = currentPlayer->getSymbol();
	//Every turn -> available - 1
	available--;
	//Human = Player_2
	currentPlayer = &player[1];
}

int Game::minimax(Board& b,int& alpha, int& beta, int depth, bool isMaximizing)
{
	Player* winner = checkWinner();
	int score = INT_MIN;
	map<string, int>::iterator itr;
	
	if (winner != NULL) {
		
		itr = scoreTable.find(winner->getSymbol());
		score = itr->second;
		return score - depth;
		
	}
	else if (available == 0 && winner == NULL) {
		
		itr = scoreTable.find("Tie");
		score = itr->second;
		return score;
	}

	if (isMaximizing) {
		int bestScore = INT_MIN;
		for (int i = 0; i < board.getHeight(); i++) {
			for (int j = 0; j < board.getWidth(); j++) {
				if (board.matrix[i][j] == initValue) {
					board.matrix[i][j] = player[0].getSymbol();
					//Next turn is human
					
					int score = minimax(board, alpha, beta, depth + 1, false);

					board.matrix[i][j] = initValue;

					//bestScore = max(score,bestScore)
					bestScore = score > bestScore ? score: bestScore;
					//alpha = max(alpha, score)
					alpha = alpha > score ? alpha : score;
					/*if (beta <= alpha)
						break;*/
				}
			}
		}
		/*cout << currentPlayer->getName() << endl;
		cout << "Depth: " << depth << endl;
		board.drawBoard();
		cout << endl;*/
		return bestScore;
	}
	else {
		int bestScore = INT_MAX;
		for (int i = 0; i < board.getHeight(); i++) {
			for (int j = 0; j < board.getWidth(); j++) {
				if (board.matrix[i][j] == initValue) {
					board.matrix[i][j] = player[1].getSymbol();
					//Next turn is computer
					
					int score = minimax(board, alpha, beta, depth + 1, true);

					board.matrix[i][j] = initValue;
					//bestScore = min(score,bestSocre)
					bestScore = score > bestScore ? bestScore : score;
					//beta = min(score,beta)
					beta = score > beta ? beta : score;
					/*if (beta <= alpha)
						break;*/
				}
			}
		}
	/*	cout << currentPlayer->getName() << endl;
		cout << "Depth: " << depth << endl;
		board.drawBoard();
		cout << endl;*/
		return bestScore;
	}
}

//who has 3 in the same line is the winner
Player* Game::checkWinner()
{
	Player* winner = NULL;
	int count = 0;
	int i = 0;
	int j = 0;

	//Horizontal check
	if(winner == NULL)
		winner = checkHorizontal(board.getWidth(), board.getHeight());
		
	//Vertical check
	if(winner == NULL)
		winner = checkVertical(board.getWidth(), board.getHeight());
	

	//Diagonal check (3 x 3), for bigger board -> update later
	if (winner == NULL)
		winner = checkDiagonal(board.getWidth(), board.getHeight());
	
	return winner;
}

Player* Game::checkHorizontal(int first_dimensional, int second_dimensional)
{
	for (int k = 0; k < 2; k++) {
		if(check_Horizontal_Line(board.getWidth(), board.getHeight(),3, player[k].getSymbol()))
			return &player[k];
	}
	return NULL;
}

Player* Game::checkVertical(int first_dimensional, int second_dimensional)
{
	for (int k = 0; k < 2; k++) {
		if (check_Vertical_Line(board.getWidth(), board.getHeight(), 3, player[k].getSymbol()))
			return &player[k];
	}
	return NULL;
}

Player* Game::checkDiagonal(int first_dimensional, int second_dimensional)
{
	for (int k = 0; k < 2; k++) {
		if (check_Diagonal_Line(board.getWidth(), board.getHeight(), 3, player[k].getSymbol()))
			return &player[k];
	}
	return NULL;
}

int Game::available_winning_move(Player& player)
{
	int count = 0;

	return count;
}

bool Game::check_Horizontal_Line(int first_dimensional, int second_dimensional, int length, string symbol)
{
	int count = 0;
	for (int i = 0; i < first_dimensional; i++) {
		for (int j = 0; j < second_dimensional; j++) {
			if (board.matrix[i][j] != symbol) {
				count = 0;
				continue;
			}

			count++;
			if (count >= length && board.matrix[i][j] == symbol) {
				return true;
			}
		}
		count = 0;
	}
	return false;
}

bool Game::check_Vertical_Line(int first_dimensional, int second_dimensional, int length, string symbol)
{
	int count = 0;
	for (int i = 0; i < first_dimensional; i++) {
		for (int j = 0; j < second_dimensional; j++) {
			if (board.matrix[j][i] != symbol) {
				count = 0;
				continue;
			}

			count++;
			if (count >= length && board.matrix[j][i] == symbol) {
				return true;
			}
		}
		count = 0;
	}
	return false;
}

bool Game::check_Diagonal_Line(int first_dimensional, int second_dimensional, int length, string symbol)
{
	int i = 0;
	int j = 0;
	int count = 0;

	for (i = 0, j = 0; i < second_dimensional, j < first_dimensional; i++, j++) {
		if (board.matrix[i][j] != symbol) {
			count = 0;
			continue;
		}

		count++;
		if (count >= length) {
			return true;
		}
	}

	count = 0;
	for (i = 0, j = first_dimensional - 1; i < second_dimensional, j >= 0; i++, j--) {
		if (board.matrix[i][j] != symbol) {
			count = 0;
			continue;
		}

		count++;
		if (count >= length) {
			return true;
		}
	}
	return false;
}

void Game::draw()
{
	board.drawBoard();
}
