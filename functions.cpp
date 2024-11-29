#include "functions.h"


#include <iostream>
#include <conio.h>
#include <windows.h>


bool gameOver;
const int height = 15;    // dimentions of game area
const int width = 30;

int x, y, ntail, score;  // pos of snake, tail pos, no of tails and score
int Xtail[100], Ytail[100] = { 0 };  // arrays for storing x, y coords of tails (at index 0 of both-> x,y of first tail)
int fruitX, fruitY;


enum eDirection { STOP, UP, DOWN, RIGHT, LEFT, };  // all possible states and directions of snake
eDirection dir;



void Setup()   // set initial conditions of the game
{
	gameOver = false;
	x = width / 2;
	y = height / 2;
	dir = STOP;
	score = 0;
	srand(time(0));
	randFruit();
	Xtail[0] = x - 1; Ytail[0] = y - 1;
	ntail = 1;
}


void randFruit()
{
	fruitX = rand() % width;
	fruitY = rand() % height;
}


void Draw() 
{
	system("cls");
	
	std::cout << "Score: " << score << '\n';
	for (int i = -1; i <= height; i++) {   // vertical -> y
		for (int j = -1; j <= width; j++) {   // horizontal -> x
			if (i == -1 || i == height)    // upper/lower boundry
				std::cout << '-';
			else if ((j == -1 || j == width) && i != - 1 && i != height) // left/right boundry
				std::cout << '|';
			else {                                
				if (j == x && i == y)    // snake head
					std::cout << 'O';
				else {           // Check for snake body
					bool isTail = false;
					for (int k = 0; k < ntail; k++) {
						if (j == Xtail[k] && i == Ytail[k]) {
							std::cout << 'o';         // snake body part
							isTail = true;
							break;
						}
					}
					if (!isTail) {        // is no tail at that i,j then fruit or empty space
						if (j == fruitX && i == fruitY)  // fruit position
							std::cout << '$';
						else
							std::cout << ' ';   // empty space
					}
				}
			}
		}
		std::cout << '\n';
	}
}


void Input()
{
	if (_kbhit()) {               // check if keyboard is hit
		switch (_getch()) {                  // get the hit char, if valid then update direction
		case 'w': if (dir != DOWN) dir = UP; break;
		case 's': if (dir != UP) dir = DOWN; break;
		case 'd': if (dir != LEFT) dir = RIGHT; break;
		case 'a': if (dir != RIGHT) dir = LEFT; break;
		default: break;
		}
	}
}


void Logic()
{           
	if (dir != STOP) {              // tail[0] -> first tail after head
		int prevX = Xtail[0];  // prevXY is temp var to transfer coords
		int prevY = Ytail[0];  // prevXY stores the 1st tail coords
		Xtail[0] = x;           // coords of head are given to 1st tail (indicating forward movement)
		Ytail[0] = y;
		int prev2X, prev2Y;     // temp var to store ith tail coords
		for (int i = 1; i < ntail; i++) {   // go through all the tails in array
			prev2X = Xtail[i];
			prev2Y = Ytail[i];       // ith tail coords stored in prev2XY 
			Xtail[i] = prevX;        // ith tail coords updated to the coords of the tail in front of it
			Ytail[i] = prevY;
			prevX = prev2X;          // prevX is given ith coord for next iteration
			prevY = prev2Y;
		}
	}
	
	switch (dir) {              // increase head-cord according to direction
	case UP: y--;  break;
	case DOWN: y++; break;
	case RIGHT: x++; break;
	case LEFT: x--; break;
	case STOP: break;
	}

	if (x == fruitX && y == fruitY) {   // eat fruit logic
		score += 10;
		ntail++;
		randFruit();
	}

	for (int i = 0; i < ntail; i++) {            // hit tail logic
		if (x == Xtail[i] && y == Ytail[i])
			gameOver = true;
	}

	if (x < 0) x = width - 1;  // wrap-around boundry
	if (y < 0) y = height - 1;
	if (x > width - 1) x = 0;
	if (y > height - 1) y = 0;
}