#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> //to seed random number gen

#include "snakelib.h"

char gameChars[4] = "+Oo@"; //im too lazy to type out the chars in an array

int main(int argc, char **argv)
{
	time_t t;
	srand((unsigned) time(&t)); //seeds random number generator with Epoch time

	initCursesEnv(); //boilerplate stuff to get ncurses to work

	grid gameGrid = {SCREEN_SIZE, SCREEN_SIZE}; // alter definition if needed
	snake snake = initSnake(SCREEN_SIZE/2, SCREEN_SIZE/2);
	apple apple = initApple(apple, gameGrid, snake);
	
	int isFirstFrame = 1;
	char input;
	char isDebugEnabled = 0;
		
	int score = 1;
	
	snake.isCollided = 0;

	while(1) //main game loop
	{
		clear();
		
		input = takeInput(isDebugEnabled, snake);
		if(input == 'G')
			snake = snakeGrow(snake, gameGrid);
		else if(input == 'M')
			isDebugEnabled = !isDebugEnabled;
		else if (input != '\0')
			snake.direction = input;
	
		snake = snakeShift(snake, gameGrid);	

		int isAppleEaten = checkAppleCollisions(snake, apple);
		if(isAppleEaten)
		{
			score++;
			snake = snakeGrow(snake, gameGrid);
			apple = initApple(apple, gameGrid, snake);
		}
		snake = snakeCheckCollide(snake);
		if(!apple.isPlaceable)
			break;
		if(snake.isCollided)
			break;

		mvprintw(gameGrid.ydim + 1, 1, "SCORE: %d", score);

		printGrid(gameGrid, snake, apple);

		printDebug(input, isDebugEnabled, snake, apple);
		
		flushinp(); //prevents stacking of key inputs, only first is considered
		refresh();
		delay(1000); //1 second plus calculation time per frame, because implementing the necessary code to make a frame a fixed length of time is beyond the scope of this project	
	}	
	if(snake.isCollided)
	{
		clear();
		mvprintw(gameGrid.xdim/2, gameGrid.ydim/2, "You lose! Your score was %d.", score);
		refresh();
	}
	else
	{
		clear();
		mvprintw(gameGrid.xdim/2, gameGrid.ydim/2, "You win! Your score was %d.", score);
		refresh();
	}
	delay(5000);
	endwin();

	free(snake.xPtr);
	free(snake.yPtr);
	return 0;
}
