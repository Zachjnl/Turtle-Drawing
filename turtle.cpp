/******************************************************************************
* Programmer: Zach Lansing
*
* CSCI 1106
* Programming Assignment 2
* Due: Dec 6 2018
* Turtle Drawing
******************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

const int ARRAY_SIZE = 500;

void penDraw(int grid[][ARRAY_SIZE], bool pen, int x, int y);
void rightTurn(int &dir);
void leftTurn(int &dir);
void displayGrid(int grid[][ARRAY_SIZE], int x, int y);
void moveTurtle(int dir, int &x, int &y, int gx, int gy);

int main(){
	int grid[ARRAY_SIZE][ARRAY_SIZE] = {0},				//variable declarations
		 penDown = false;			//false is up, true is down
	char turtleSteps;
	int turtleX = 0,				//Starts at (0,0)
		turtleY = 0,
		gridX = 50,					//Drawing area is 50 wide by 8 high
		gridY = 8,
		numSteps,
		turtleDir = 1;				//0 = North, 1 = East, 2 = South, 3 = West
	ifstream inFile;
	
	inFile.open("turtle.txt");		//Get file and check for file errors
	if(!inFile){
		cout << "Error opening file!" << endl;
		exit(1106);
	}//end if
	
	while(inFile >> turtleSteps){				//Gets instruction from file
		switch(turtleSteps){
			case 'u':
			case 'U': penDown = false;
					  break;
			case 'd':
			case 'D': penDown = true;		//Changes val at pen press for dot
					  grid[turtleY][turtleX] = 1;
					  break;
			case 'r':
			case 'R': rightTurn(turtleDir);
					  break;
			case 'l':
			case 'L': leftTurn(turtleDir);
					  break;
			case 'f':
			case 'F': inFile >> numSteps;		//Move num of steps specified
					  for(int i = 0; i < numSteps; i++){
						 moveTurtle(turtleDir, turtleX, turtleY, gridX, gridY);
						 penDraw(grid, penDown, turtleX, turtleY);
					  }
					  break;
			case 'p':
			case 'P': displayGrid(grid, gridX, gridY);
					  break;
			case 'q':
			case 'Q': inFile.close();	//Closes file when last step is reached
					  break;
		}
	}
	return 0;
}//end main

/********************************displayGrid***********************************
*Description:	Displays the drawing area with * for 1 and ' ' for 0
*
*Pre:	Gets grid and max x and y of drawing area
*Post:	Outputs drawing to screen
******************************************************************************/
void displayGrid(int grid[][ARRAY_SIZE], int x, int y){
	for(int i = 0; i < y; i++){
		for(int j = 0; j < x; j++)
			(grid[i][j] == 1) ? cout << "*" : cout << " ";//'*' for 1 else ' '
		cout << endl;
	}//end outer for
}

/***********************************penDraw************************************
*Description:	Changes grid cell value to 1 if pen is down
*
*Pre:	Turtle location, and pen status
*Post:	Changes value at current location if pen is down
******************************************************************************/
void penDraw(int grid[][ARRAY_SIZE], bool pen, int x, int y){
	if(pen)
		grid[y][x] = 1;
}

/********************************moveTurtle************************************
*Description:	Moves turtle inside the drawing area
*
*Pre:	Gets current direction, x and y coordinates, and max grid x and y
*Post:	Changes turtle x or y coordinate based on direction
******************************************************************************/
void moveTurtle(int dir, int &x, int &y, int gx, int gy){
	switch(dir){
		case 0: if(y > 0)	//only moves if in the drawing area
					y--;	//north
				  break;
		case 1: if(x < gx)
					x++;	//east
				  break;
		case 2: if(y < gy)
					y++;	//south
				  break;
		case 3: if(x > 0)
					x--;	//west
				  break;
	}
}

/********************************rightTurn*************************************
*Description:	Changes turtle direction right one
*
*Pre:	Gets current direction
*Post:	Changes direction right one
******************************************************************************/
void rightTurn(int &dir){
	if(dir == 3)	//if looking west
		dir = 0;	//turn north
	else
		dir++;
}

/********************************leftTurn**************************************
*Description:	Changes turtle direction left one
*
*Pre:	Gets current direction
*Post:	Changes direction left one
******************************************************************************/
void leftTurn(int &dir){
	if(dir == 0)	//if looking north
		dir = 3;	//turn west
	else
		dir--;
}