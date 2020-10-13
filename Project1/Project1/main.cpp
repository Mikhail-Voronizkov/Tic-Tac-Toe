#include<iostream>
#include"Board.h"
#include"Game.h"

using namespace std;

int main() {
	int choice = 1;

	while (choice != 0) {
		cout << "=== TIC TAC TOE ===" << endl;
		cout << ">Press 1 to play. Press 0 to exit" << endl;
		cout << ">> ";
		cin >> choice;

		if (choice == 1) {
			string s = "-";
			Game tic(3, 3, s);
			tic.run();
			cout << "End game" << endl;
		}
		system("cls");
	}
	
	
	return 0;
}