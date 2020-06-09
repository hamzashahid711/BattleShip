#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ncurses/ncurses.h>

#define ROWS 10
#define COLUMNS 10

char playerField[COLUMNS][ROWS];
char computerField[COLUMNS][ROWS];
char userView[COLUMNS][ROWS];

typedef struct Coordinate{
	int x;
	int y;
	int hit;
}Coordinate;

typedef struct Battleships{
	Coordinate carrier[3];
	Coordinate destroyer[2];
	Coordinate patrolBoat;
}Battleships;

void printField(int a);
Battleships generateComputerShips();
void draw_character(int row, int column, char use);
Battleships shipSelection();
int checkWin(int b);
void userTurn();
void computerTurn();
//functions
//Battleships generateComputerShips();
//generate fire for computer on player
//print the fire
//check status of game function(to check if someone won)





int main(void){


	Battleships playerShips;
	Battleships computerShips;

	srand(time(NULL));

	initscr();
    refresh();

	//Fill the players field with the default character
	for(int i = 0; i < COLUMNS;i++){
		for(int j = 0; j<ROWS;j++){

			userView[i][j] = '~';
			computerField[i][j] = '~';
			playerField[i][j] = '~';
		}

	}
	for(int i = 0; i < COLUMNS; i++){

		mvprintw(1, 2*i + 26, "%d", i);

	}

	generateComputerShips();
	printField(1);
	printField(0);

	mvprintw(0,3,"Computer's Field");

	//the function to ask the user to enter their ships
	shipSelection();

	printField(0);
    refresh();

	while(1){

		//Users turn here
		userTurn();
		printField(1);

		//Computer's turn here
		computerTurn();
		printField(0);

		//checks if someone has won
		if(checkWin(1) == 1){

			endwin();
			printf("You Win!");

			break;
		}
		if(checkWin(0) == 1){

			endwin();
			printf("The Computer Wins!");
			break;
		}
	}

	endwin();

	return 0;
}

void printField(int a){

	//prints the values for the computer's field
	if(a){
		for(int i = 0; i<COLUMNS+1;i++){
			for(int j = 1;j<ROWS+2;j++){
				if(j == 1 && i >0)
					draw_character(i+i,j,(47 + i));
				else if(i == 0 && j >1)
					draw_character(i+i,j,(63 + j));
				else if(i!=0 && j!=1)
					draw_character(i+i,j,userView[i-1][j-2]);
			}
		}
	}

	//prints the values for the player's field
	if(!a){
		for(int i = 12; i<COLUMNS+13;i++){
			for(int j = 1;j<ROWS+2;j++){
				if(i!=12 && j!=1)
					draw_character(i+i,j,playerField[i-13][j-2]);
			}
		}
	}

}

Battleships generateComputerShips(){

	int row, col, orientation;

	orientation = rand() % 2;


	//gets values for the carrier

	//right
	if(orientation == 0){
		col = rand() % 8;
		row = rand() % 10;
		computerField[col][row] = 'O';
		computerField[col + 1][row] = 'O';
		computerField[col + 2][row] = 'O';
	}
	//down
	if(orientation == 1){
		col = rand() % 10;
		row = rand() % 8;
		computerField[col][row] = 'O';
		computerField[col][row + 1] = 'O';
		computerField[col][row + 2] = 'O';
	}

	//gets the values for the destroyer
	orientation = rand() % 2;

	//right
	if(orientation == 0){

		//prevents ships from overlapping
		while(1){
			col = rand() % 9;
			row = rand() % 10;

			if(computerField[col][row] != 'O' && computerField[col + 1][row] != 'O'){
				computerField[col][row] = 'O';
				computerField[col + 1][row] = 'O';
				break;
			}

		}

	}
	//down
	if(orientation == 1){

		//prevents ships from overlapping
		while(1){
			col = rand() % 10;
			row = rand() % 9;
			if(computerField[col][row] != 'O' && computerField[col][row + 1] != 'O'){
				computerField[col][row] = 'O';
				computerField[col][row + 1] = 'O';
			break;
			}

		}
	}
	//gets the value for the patrol boat
	orientation = rand() % 2;

	//right
	if(orientation == 0){

		//prevents ships from overlapping
		while(1){

			col = rand() % 10;
			row = rand() % 10;
			if(computerField[col][row] != 'O'){
				computerField[col][row] = 'O';
				break;
			}

		}
	}
	//down
	if(orientation == 1){

		//prevents ships from overlapping
		while(1){

			col = rand() % 10;
			row = rand() % 10;
			if(computerField[col][row] != 'O'){
				computerField[col][row] = 'O';
				break;
			}

		}


	}
}
Battleships shipSelection(){

	char carrierRowStartc,  destroyerRowStartc,  patrolRowc;
	int carrierRowStart,  destroyerRowStart,  patrolRow;
	int carrierColumnStart,  destroyerColumnStart,  patrolColumn;
	char carrierDirection, destroyerDirection;
	mvprintw(0,30,"Your Field");

	//Gets the starting point for the carrier ship
	mvprintw(30, 1, "Enter the starting coordinate for the carrier(Ex: D5)");
	mvscanw(31, 1, "%c%d", &carrierRowStartc, &carrierColumnStart);

		//converts the letter input into numbers
		carrierRowStart = carrierRowStartc - 'A';

	playerField[carrierColumnStart][carrierRowStart] = 'O';
	mvprintw(30, 1, "                                                            ");
	mvprintw(31, 1, "      ");

	printField(0);
	refresh();

	//gets the direction for the carrier ship and changes values accordingly
	mvprintw(30, 1, "Enter the direction for this ship. U for up, D for down, L for left, R for right");
	mvscanw(31, 1, "%c", &carrierDirection);
	if(carrierDirection == 'U'){
		playerField[carrierColumnStart][carrierRowStart - 1] = 'O';
		playerField[carrierColumnStart][carrierRowStart - 2] = 'O';
	}
	if(carrierDirection == 'D'){
		playerField[carrierColumnStart][carrierRowStart + 1] = 'O';
		playerField[carrierColumnStart][carrierRowStart + 2] = 'O';
	}
	if(carrierDirection == 'L'){
		playerField[carrierColumnStart - 1][carrierRowStart] = 'O';
		playerField[carrierColumnStart - 2][carrierRowStart] = 'O';
	}
	if(carrierDirection == 'R'){
		playerField[carrierColumnStart + 1][carrierRowStart] = 'O';
		playerField[carrierColumnStart + 2][carrierRowStart] = 'O';
	}
	mvprintw(30, 1, "                                                                                                    ");
	mvprintw(31, 1, "      ");

	printField(0);
	refresh();


	//Gets the starting point for the destroyer ship
	mvprintw(30, 1, "Enter the starting coordinate for the destroyer(Ex: D5)");
	mvscanw(31, 1, "%c%d", &destroyerRowStartc, &destroyerColumnStart);

		//converts the letter input into numbers
		destroyerRowStart = destroyerRowStartc - 'A';

	playerField[destroyerColumnStart][destroyerRowStart] = 'O';
	mvprintw(30, 1, "                                                            ");
	mvprintw(31, 1, "      ");

	printField(0);
	refresh();

	//gets the direction for the destroyer ship and changes values accordingly
	mvprintw(30, 1, "Enter the direction for this ship. U for up, D for down, L for left, R for right");
	mvscanw(31, 1, "%c", &destroyerDirection);
	if(destroyerDirection == 'U'){
		playerField[destroyerColumnStart][destroyerRowStart - 1] = 'O';
	}
	if(destroyerDirection == 'D'){
		playerField[destroyerColumnStart][destroyerRowStart + 1] = 'O';
	}
	if(destroyerDirection == 'L'){
		playerField[destroyerColumnStart - 1][destroyerRowStart] = 'O';
	}
	if(destroyerDirection == 'R'){
		playerField[destroyerColumnStart + 1][destroyerRowStart] = 'O';
	}
	mvprintw(30, 1, "                                                                                                    ");
	mvprintw(31, 1, "      ");

	printField(0);
	refresh();

	mvprintw(30, 1, "Enter the coordinate for the patrol boat(Ex: D5)");
	mvscanw(31, 1, "%c%d", &patrolRowc, &patrolColumn);

		//converts the letter input into numbers
		patrolRow = patrolRowc - 'A';

	playerField[patrolColumn][patrolRow] = 'O';

	mvprintw(30, 1, "                                                                                                    ");
	mvprintw(31, 1, "      ");

	printField(0);
	refresh();
}
void draw_character(int row, int column, char use)
{
    mvaddch(column, row, use);
    refresh();
}
int checkWin(int b){

	//will return false if the computer finds an O in the computer's field. This means there is still at least one ship
	if(b){
		for(int i = 0; i < COLUMNS;i++){
			for(int j = 0; j<ROWS;j++){
				if(computerField[i][j] == 'O'){
					return 0;
				}

			}

		}
	return 1;
	}
	//checks the player field for an O. returns false if one is present and true if one is found
	if(!b){
		for(int i = 0; i < COLUMNS;i++){
			for(int j = 0; j<ROWS;j++){
				if(playerField[i][j] == 'O'){
					return 0;
				}

			}

		}
	return 1;
	}
}

void userTurn(){
	char row;
	int col, numRow;

	mvprintw(30, 1, "Enter a move:");
	mvscanw(31, 1, "%c%d", &row, &col);

	//converts to a number of rows
	numRow = row - 'A';

	//prints X if a hit
	if(computerField[col][numRow] == 'O'){
		computerField[col][numRow] = 'X';
		userView[col][numRow] = 'X';

		//prints M if a miss
	}else{
		computerField[col][numRow] = 'M';
		userView[col][numRow] = 'M';

	}

	mvprintw(30, 1, "                                                                      ");
	mvprintw(31, 1, "           ");
	refresh();

}

void computerTurn(){
	int row, col;
	row = rand() % 10;
	col = rand() % 10;

	//Stops the computer from playing on the same space twice
	if(playerField[col][row] == 'M' || playerField[col][row] == 'X'){
		computerTurn();
	}
	//prints X if a hit
	if(playerField[col][row] == 'O'){
		playerField[col][row] = 'X';

		//prints M if a miss
	}else{
		playerField[col][row] = 'M';

	}

	refresh();


}
