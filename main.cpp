#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include <unistd.h>
#include <graphics.h>
using namespace std;

const int GRID_SIZE = 2;
int totalMove = (GRID_SIZE * GRID_SIZE + GRID_SIZE) * 2;
char grid[GRID_SIZE * 2 + 1][GRID_SIZE * 2 + 1];
const int BOX_SIZE = 50;
const int DOT_RADIUS = 5;


void getPlayerMove(int& row, int& col) {
    cout << "Enter the row - column numbers: ";
    cin >> row >> col;
}

bool isValidMove(int& row, int& col) {
	if(row % 2 == 0 && col % 2 == 1) return true;
    else if(row % 2 == 1 && col % 2 == 0) return true;
    return false;
}

void drawGrid(char grid[][GRID_SIZE * 2 + 1]) {
	
    for (int i = 0; i < GRID_SIZE * 2 + 1; i++) {
        for (int j = 0; j < GRID_SIZE * 2 + 1; j++) {
        	if(i % 2 == 0 && j % 2 == 0) {
        		cout << ".";
            	readimagefile("D:\\Coding\\DotsAndBoxes\\flower.jpg", j * BOX_SIZE, i * BOX_SIZE, j * BOX_SIZE + 20, i * BOX_SIZE +20);
			}
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
        outtextxy(250, 250, "Player 1 wins!");
    } else if (player1Score < player2Score) {
        cout << "Player 2 wins!" << endl;
        outtextxy(250, 250, "Player 2 wins!");
    } else {
        cout << "It's a draw!" << endl;
        outtextxy(250, 250, "It's a draw!");
    }
}

void connectDots(int x1, int y1, int x2, int y2) {
    line(x1, y1, x2, y2);
}


int main() {
	int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    readimagefile("D:\\Coding\\DotsAndBoxes\\background.jpg", 0, 0, getmaxx(), getmaxy());
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand((int)time(0));
	int P1Score = 0;
	int P2Score = 0;
    bool isPlayer1Turn = true;
    
    setcolor(BLUE);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    while (totalMove > 0) {
    int player1Score = 0;
    int player2Score = 0;
  	for(int i = 0; i < 25; i++) cout << endl;  
	if(isPlayer1Turn == true) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	 	cout << "It's P1's turn." << endl;
	 	outtextxy(250, 250, "It's P1's turn.");
	}else{
		 SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		 cout << "It's P2's turn." << endl;
		 outtextxy(250, 250, "It's P2's turn.");
	}
	     
        drawGrid(grid);

        int row, col;
		getPlayerMove(row, col);
		
		char symbol;
        if(row % 2 == 0 && col % 2 == 1) {
        	symbol = '-';
        	setcolor(RED);
    		connectDots((col - 1) * BOX_SIZE, row * BOX_SIZE + 10, (col + 1) * BOX_SIZE, row * BOX_SIZE + 10);

		}	
		else if(row % 2 == 1 && col % 2 == 0) {
			symbol = '|';
			setcolor(RED);
			connectDots(col* BOX_SIZE + 10, (row - 1) * BOX_SIZE, col* BOX_SIZE + 10, (row + 1) * BOX_SIZE);
		}
       	updateGrid(grid, row, col, symbol);

       	if (isBoxCompleted(grid, row, col) == true) {
           	assignBoxToPlayer(grid, row, col, isPlayer1Turn);
       	}else isPlayer1Turn = !isPlayer1Turn;
       	
       	totalMove--;
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
    
    sleep(100);
    closegraph();
    return 0;
}
