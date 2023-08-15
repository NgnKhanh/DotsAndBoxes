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

void assignBoxToPlayer(int& player1Score, int& player2Score, bool isPlayer1Turn) {
    if (isPlayer1Turn) player1Score++;
    else player2Score++;
}

bool isGameOver(int player1Score, int player2Score) {
    return (player1Score + player2Score) == (GRID_SIZE * GRID_SIZE);
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
    int player1Score = 0;
    int player2Score = 0;
    bool isPlayer1Turn = true;

    while (!isGameOver(player1Score, player2Score)) {
  	    
    cout << "P1 Score: " << player1Score << endl
	     << "P2 Score: " << player2Score << endl;  
	     
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
           	assignBoxToPlayer(player1Score, player2Score, isPlayer1Turn);
       	}else isPlayer1Turn = !isPlayer1Turn;
    }

    drawGrid(grid);
    declareWinner(player1Score, player2Score);

    return 0;
}
