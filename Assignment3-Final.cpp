#include<iostream>
#include<cstdlib>
#include<ctime>
#include <chrono>
#include <thread>

using namespace std;
class game {
protected:
	int noOfMines;
	const int noOfCells = 225;
	const int rows = 15;
	const int columns = 15;
	int r, c;
	char m;
	char displayBoard[15][15];
	char valueBoard[15][15] = { '0' };
	chrono::steady_clock::time_point startTime;
	int noOfFlags;
public:
	game();
	void StartGame();//shows menu
	void showBoard();//done and right
	void setMines(int m);
	void takeInput();
	void exposeMines();
	void initializeDisplayBoard();
	virtual void initializeValueBoard() = 0;
	void startTimer();
	void ifZero(int r, int c);
	void displayElapsedTime()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsedSeconds = chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
		cout << "Elapsed Time: " << elapsedSeconds << " seconds" << endl;
	}
	bool isGameOver();
};
void game::startTimer()
{
	startTime = chrono::steady_clock::now();
}

game::game() {
	noOfMines = 0;
	r = 0; c = 0;
	m = 0; noOfFlags = 0;
}
void game::setMines(int m) {
	noOfMines = m;
}
void game::StartGame() {
	initializeDisplayBoard();
	cout << "Welcome to Minesweeper!\n";
	cout << "Instructions: Enter row and column (0-indexed) to reveal the cell.\n";
	startTimer();
	showBoard();

	while (!isGameOver()) {
		takeInput();
		showBoard();
		displayElapsedTime();
	}
	showBoard();
	displayElapsedTime();
}
void game::initializeDisplayBoard() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			displayBoard[i][j] = '-';
		}
	}
}
void game::showBoard() {
	cout << " ";
	for (int i = 0; i < columns; i++) {
		cout << "----";
	}
	cout << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << "| " << displayBoard[i][j] << " ";
			if (j == columns - 1) {
				cout << "|";
			}
		}
		cout << endl;

	}
	cout << " ";
	for (int i = 0; i < columns; i++) {
		cout << "----";
	}
	cout << endl;
}
void game::takeInput() {
	cout << "Enter row and column: ";
	cin >> r >> c;
	if (r < 0 || r >= rows || c < 0 || c >= columns) {
		cout << "Invalid input! Please enter valid row and column.\n";
		return;
	}
	cout << "Enter R or L: ";
	cin >> m;
	if (m == 'L') {

		if (displayBoard[r][c] != '-') {
			cout << "Cell already revealed or flagged! Please choose another.\n";
			return;
		}

		if (valueBoard[r][c] == '*') {
			cout << "Game over! You hit a mine.\n";
			exposeMines();
			showBoard();
			displayElapsedTime();
			exit(0);
			return;
		}
		if (valueBoard[r][c] == '0') {
			displayBoard[r][c] = 0;
			ifZero(r, c);
		}
		
		displayBoard[r][c] = valueBoard[r][c];
	}
	else if (m == 'R') {
		if (noOfFlags == noOfMines) {
			cout << "Limits of Flagged cells reached.";
			return;
		}
		if (displayBoard[r][c] != '-') {
			cout << "Cell already revealed! Please choose another.\n";
			return;
		}
		displayBoard[r][c] = 'F';
		noOfFlags++;
	}
}
void game::ifZero(int row, int col) {
	//if (row-1 >= 0 && row+1 < rows && col-1 >= 0 && col+1 < columns) {
	if (row - 1 >= 0) {
		if (displayBoard[row - 1][col] != 'F') {
			displayBoard[row - 1][col] = valueBoard[row - 1][col];
			if (valueBoard[row-1][col] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row-1][col] == '0')
				ifZero(row-1, col);
		}
	}//done
	if (col - 1 > 0) {
		if (displayBoard[row][col - 1] != 'F') {
			displayBoard[row][col - 1] = valueBoard[row][col - 1];
			if (valueBoard[row][col - 1] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row][col - 1] == '0')
				ifZero(row, col-1);
		}
		//done`
	}
	if (row - 1 >= 0 && col - 1>=0) {
		if (displayBoard[row - 1][col - 1] != 'F') {
			displayBoard[row - 1][col - 1] = valueBoard[row - 1][col - 1];
			if (valueBoard[row - 1][col - 1] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row - 1][col - 1] == '0')
				ifZero(row - 1, col-1);
		}//done
		
	}
	if (row + 1 < this->rows) {
		if (displayBoard[row + 1][col] != 'F') {
			displayBoard[row + 1][col] = valueBoard[row + 1][col];
			if (valueBoard[row + 1][col] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row + 1][col] == '0')
				ifZero(row + 1, col);
		}
	}
	if (col + 1 < this->columns) {
		if (displayBoard[row][col + 1] != 'F') {
			displayBoard[row][col + 1] = valueBoard[row][col + 1];
			if (valueBoard[row][col + 1] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row][col + 1] == '0')
				ifZero(row , col+1);
		}
//zero
	}
	if (row + 1 < this->rows && col + 1 < this->columns) {
		if (displayBoard[row+1][col +1] != 'F') {
			displayBoard[row+1][col+ 1] = valueBoard[row][col - 1];
			if (valueBoard[row+1][col + 1] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row+1][col +1] == '0')
				ifZero(row + 1, col+1);
		}
		//done
	
	}
	if (row - 1 > 0 && col + 1 < this->columns) {
		if (displayBoard[row-1][col +1] != 'F') {
			displayBoard[row-1][col + 1] = valueBoard[row][col - 1];
			if (valueBoard[row-1][col + 1] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row-1][col +1] == '0')
				ifZero(row - 1, col+1);
		}

		
	}
	if (row + 1 < this->rows && col - 1 > 0) {
		if (displayBoard[row+1][col - 1] != 'F') {
			displayBoard[row+1][col - 1] = valueBoard[row][col - 1];
			if (valueBoard[row+1][col - 1] == '*') {
				cout << "Game over! You hit a mine.\n";
				exposeMines();
				showBoard();
				displayElapsedTime();
				exit(0);
				return;
			}
			if (valueBoard[row+1][col - 1] == '0')
				ifZero(row +1, col-1);
		}
		
		
	}
}

void game::exposeMines()
{
	for (int i = 0; i < this->rows; i++) {

		for (int j = 0; j < this->columns; j++) {

			if (valueBoard[i][j] == '*') {
				displayBoard[i][j] = valueBoard[i][j];
			}
		}

	}
}
bool game::isGameOver() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (displayBoard[i][j] == '-' && valueBoard[i][j] != '*') {
				return false;
			}
		}
	}
	return true;
}
class easy :public game {
public:
	virtual void initializeValueBoard() {

		setMines(10);
		int count = 0;
		while (count < noOfMines) {
			int row = rand() % rows;
			int col = rand() % columns;
			if (valueBoard[row][col] != '*') {
				valueBoard[row][col] = '*';
				++count;
			}
		}
		int count2 = 0;
		while (count2 < 150) {
			int row = rand() % rows;
			int col = rand() % columns;
			int random_number = rand() % 9+1;
			if (valueBoard[row][col] != '*' && valueBoard[row][col] != '1') {
				valueBoard[row][col] = random_number;
				++count2;
			}
		}
		int count3 = 0;
		while (count3 < 65) {
			int row = rand() % rows;
			int col = rand() % columns;
			if (valueBoard[row][col] != '*' && valueBoard[row][col] != '1' && valueBoard[row][col] != '0') {
				valueBoard[row][col] = '0';
				++count3;
			}
		}
	}
};
class medium :public game {
public:
	virtual void initializeValueBoard() {
		setMines(40);
		int count = 0;
		while (count < noOfMines) {
			int row = rand() % rows;
			int col = rand() % columns;
			if (valueBoard[row][col] != '*') {
				valueBoard[row][col] = '*';
				++count;
			}
		}
		int count2 = 0;
		while (count2 < 130) {
			int row = rand() % rows;
			int col = rand() % columns;
			int random_number = rand() % 9+1;
			if (valueBoard[row][col] != '*' && valueBoard[row][col] != '1') {
				valueBoard[row][col] = random_number;
				++count2;
			}
		}
		int count3 = 0;
		while (count3 < 55) {
			int row = rand() % rows;
			int col = rand() % columns;
			if (valueBoard[row][col] != '*' && valueBoard[row][col] != '1' && valueBoard[row][col] != '0') {
				valueBoard[row][col] = '0';
				++count3;
			}
		}
	}
};
class hard :public game {
public:
	virtual void initializeValueBoard() {
		setMines(99);
		int count = 0;
		while (count < noOfMines) {
			int row = rand() % rows;
			int col = rand() % columns;
			if (valueBoard[row][col] != '*') {
				valueBoard[row][col] = '*';
				++count;
			}
		}
		int count2 = 0;
		while (count2 < 85) {
			int row = rand() % rows;
			int col = rand() % columns;
			int random_number = rand() % 9+1;
			if (valueBoard[row][col] != '*' && valueBoard[row][col] != '1') {
				valueBoard[row][col] = random_number;
				++count2;
			}
		}
		int count3 = 0;
		while (count3 < 41) {
			int row = rand() % rows;
			int col = rand() % columns;
			if (valueBoard[row][col] != '*' && valueBoard[row][col] != '1' && valueBoard[row][col] != '0') {
				valueBoard[row][col] = '0';
				++count3;
			}
		}
	}
};

int main() {
	srand(time(0)); // Seed the random number generator

	game* b1 = nullptr; // Declare a pointer to a game object and initialize to nullptr
	int v;

	cout << "Enter your Level: \n1.Easy\n2.Medium\n3.Hard\n";
	cin >> v;

	if (v < 1 || v > 3) {
		cout << "Invalid level. Exiting...\n";
		return 0;
	}

	if (v == 1) {
		b1 = new easy(); // Dynamically allocate an 'easy' object and assign its address to b1
	}
	else if (v == 2) {
		b1 = new medium(); // Dynamically allocate a 'medium' object and assign its address to b1
	}
	else {
		b1 = new hard(); // Dynamically allocate a 'hard' object and assign its address to b1
	}

	b1->StartGame(); // Start the game using the appropriate object

	delete b1; // Deallocate the memory when done with the game
	return 0;
}
