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

	while (available > 0 && winner == NULL) {

		cout <<"It's "<< currentPlayer->getName() <<"'s turn" << endl;
		
		//Computer = player[0]
		if (currentPlayer == &player[0] && winner == NULL) {
			nextTurn();
		}
		else if (currentPlayer == &player[1] && winner == NULL) {
			input();
		}

		winner = checkWinner();
		if (winner != NULL) {
			cout << endl << ">Result: " << winner->getName() << endl;
			Sleep(10000);
		}
		else if (available == 0) {
			cout << endl << ">Result: " << "Tie" << endl;
			Sleep(10000);
		}
		draw();
	}
	

	/*cout << "winner: " << winner->getName() << endl;
	cout << "End game" << endl;*/
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
	string symbol[2];
	symbol[0] = "x";
	symbol[0] = "o";
	bool win = false;
	int count = 0;
	int i = 0;
	int j = 0;

	//Horizontal check
	for (i = 0; i < board.getHeight(); i++) {
		for (j = 0; j < board.getWidth() - 1; j++) {
			if (board.matrix[i][j] == initValue || board.matrix[i][j] != board.matrix[i][j + 1]) {
				count = 0;
				continue;
			}
			
			count++;
			if (count >= 2) {
				for (int k = 0; k < 2; k++) {
					if (board.matrix[i][j] == player[k].getSymbol())
						return &player[k];
				}
			}
			
		}
		count = 0;
	}
	//Vertical check
	for (i = 0; i < board.getWidth(); i++) {
		for (j = 0; j < board.getHeight() - 1; j++) {
			if (board.matrix[j][i] == initValue || board.matrix[j][i] != board.matrix[j + 1][i]) {
				count = 0;
				continue;
			}

			count++;
			if (count >= 2) {
				for (int k = 0; k < 2; k++) {
					if (board.matrix[j][i] == player[k].getSymbol())
						return &player[k];
				}
			}
		}
		count = 0;
	}
	//Diagonal check (3 x 3), for bigger board -> update later
	/*for (i = 0, j = 0; i < board.getHeight() - 1, j < board.getWidth() - 1; i++, j++) {
		if (board.matrix[i][j] == initValue || board.matrix[i][j] != board.matrix[i + 1][j + 1]) {
			count = 0;
			continue;
		}

		count++;
		if (count >= 2) {
			for (int k = 0; k < 2; k++) {
				if (board.matrix[i][j] == player[k].getSymbol())
					return &player[k];
			}
		}
		count = 0;
	}

	for (i = 0, j = board.getWidth() - 1; i < board.getHeight() - 1, j > 0; i++, j--) {
		if (board.matrix[i][j] == initValue || board.matrix[i][j] != board.matrix[i + 1][j - 1]) {
			count = 0;
			continue;
		}

		count++;
		if (count >= 2) {
			cout << "There is a winner" << endl;
			for (int k = 0; k < 2; k++) {
				if (board.matrix[i][j] == player[k].getSymbol())
					return &player[k];
			}
		}
		count = 0;
	}*/

	for (int k = 0; k < 2; k++) {
		if ((board.matrix[0][0] == board.matrix[1][1])
			&& (board.matrix[1][1] == board.matrix[2][2])
			&& (board.matrix[2][2] == player[k].getSymbol()))
			return &player[k];
		else if ((board.matrix[0][2] == board.matrix[1][1])
				&& (board.matrix[1][1] == board.matrix[2][0])
				&& (board.matrix[2][0] == player[k].getSymbol()))
			return &player[k];
	}
	
	return NULL;
}

void Game::draw()
{
	board.drawBoard();
}
