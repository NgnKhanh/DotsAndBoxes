#include<iostream>
#include<stdlib.h>
#include<windows.h>
using namespace std;

const int GRID_SIZE = 2;

char grid[GRID_SIZE * 2 + 1][GRID_SIZE * 2 + 1];

void getPlayerMove(int& row, int& col) {
    cout << "Enter the row - column numbers: ";
    cin >> row >> col;
}

void drawGrid(char grid[][GRID_SIZE * 2 + 1]) {
	
    for (int i = 0; i < GRID_SIZE * 2 + 1; i++) {
        for (int j = 0; j < GRID_SIZE * 2 + 1; j++) {
        	if(i % 2 == 0 && j % 2 == 0) cout << ".";
            else cout << grid[i][j];
        }
        cout << endl;
    }
}

void updateGrid(char grid[][GRID_SIZE * 2 + 1], int row, int col, char symbol) {
        grid[row][col] = symbol;
    
}


bool isBoxCompleted(const char grid[][GRID_SIZE * 2 + 1], int &row, int &col) {
    if (grid[row][col] == '-' &&
        grid[row + 1][col - 1] == '|' &&
        grid[row + 1][col + 1] == '|' &&
		grid[row + 2][col] == '-') {
        return true;
    }

    else if (grid[row][col] == '-' &&
    	grid[row - 1][col - 1] == '|' &&
    	grid[row - 1][col + 1] == '|' &&
		grid[row - 2][col] == '-') {
    	return true;
	}

	else if (grid[row][col] == '|' &&
    	grid[row][col + 2] == '|' &&
    	grid[row - 1][col + 1] == '-' &&
		grid[row + 1][col + 1] == '-') {
    	return true;
	}

	else if (grid[row][col] == '-' &&
    	grid[row + 1][col - 1] == '|' &&
    	grid[row + 1][col + 1] == '|' &&
		grid[row + 2][col] == '-') {
    	return true;
	}
    return false;
}

void assignBoxToPlayer(char grid[][GRID_SIZE * 2 + 1], int &row, int &col, bool isPlayer1Turn) {
    if (isPlayer1Turn) {
    	if (grid[row][col] == '-' &&
        grid[row + 1][col - 1] == '|' &&
        grid[row + 1][col + 1] == '|' &&
		grid[row + 2][col] == '-') {
        grid[row + 1][col] = 'X';
    	}

    	if (grid[row][col] == '-' &&
   		grid[row - 1][col - 1] == '|' &&
    	grid[row - 1][col + 1] == '|' &&
		grid[row - 2][col] == '-') {
    	grid[row - 1][col] = 'X';
		}
		
		if (grid[row][col] == '|' &&
    	grid[row][col + 2] == '|' &&
    	grid[row - 1][col + 1] == '-' &&
		grid[row + 1][col + 1] == '-') {
    	grid[row][col + 1] = 'X';
		}

		if (grid[row][col] == '-' &&
    	grid[row + 1][col - 1] == '|' &&
    	grid[row + 1][col + 1] == '|' &&
		grid[row + 2][col] == '-') {
    	grid[row][col - 1] = 'X';
		}

    }else{
    	if (grid[row][col] == '-' &&
    	grid[row + 1][col - 1] == '|' &&
    	grid[row + 1][col + 1] == '|' &&
		grid[row + 2][col] == '-') {
    	grid[row + 1][col] = 'O';
		}

		if (grid[row][col] == '-' &&
    	grid[row - 1][col - 1] == '|' &&
    	grid[row - 1][col + 1] == '|' &&
		grid[row - 2][col] == '-') {
    	grid[row - 1][col] = 'O';
		}

		if (grid[row][col] == '|' &&
    	grid[row][col + 2] == '|' &&
    	grid[row - 1][col + 1] == '-' &&
		grid[row + 1][col + 1] == '-') {
    	grid[row][col + 1] = 'O';
		}

		if (grid[row][col] == '-' &&
    	grid[row + 1][col - 1] == '|' &&
    	grid[row + 1][col + 1] == '|' &&
		grid[row + 2][col] == '-') {
    	grid[row][col - 1] = 'O';
		}
	}
}

void declareWinner(int player1Score, int player2Score) {
    if (player1Score > player2Score) {
        cout << "Player 1 wins!" << endl;
    } else if (player1Score < player2Score) {
        cout << "Player 2 wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }
}


int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int P1Score = 0;
	int P2Score = 0;
    bool isPlayer1Turn = true;
    int move = (GRID_SIZE * GRID_SIZE + GRID_SIZE) * 2;

    while (move > 0) {
    int player1Score = 0;
    int player2Score = 0;
  	for(int i = 0; i < 25; i++) cout << endl;  
	if(isPlayer1Turn == true) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	 	cout << "It's P1's turn." << endl;
	}else{
		 SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		 cout << "It's P2's turn." << endl;
	}
	     
        drawGrid(grid);

        int row, col;
        getPlayerMove(row, col);
        
		char symbol;
        if(row % 2 == 0 && col % 2 == 1) symbol = '-';
       	else if(row % 2 == 1 && col % 2 == 0) symbol = '|';
       
       	updateGrid(grid, row, col, symbol);

       	if (isBoxCompleted(grid, row, col) == true) {
           	assignBoxToPlayer(grid, row, col, isPlayer1Turn);
       	}else isPlayer1Turn = !isPlayer1Turn;
       	
       	move--;
    }
    
    for (int i = 0; i < GRID_SIZE * 2 + 1; i++) {
        for (int j = 0; j < GRID_SIZE * 2 + 1; j++) {
        	if(grid[i][j] == 'X') P1Score++;
            else if(grid[i][j] == 'O') P1Score++;
        }
        cout << endl;
    }

	drawGrid(grid);
    declareWinner(P1Score, P2Score);

    return 0;
}
