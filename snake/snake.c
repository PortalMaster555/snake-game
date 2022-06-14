#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#ifdef _WIN32
  	#include <windows.h>
#else
  	#include <unistd.h>
#endif

//FUNCTIONS

void printGrid(int applePos[2], int (*snakePos)[2], int dims[2], char chars[4], int *lengthPointer)
{ //chars are + @ O o
	for(int y = 0; y < dims[1]; y++)
	{
		for(int x = 0; x < dims[0]; x++)
		{
			addch(chars[0]);
			addch(' ');
		}
		addch('\n');
	}
	//NOTE: y, x, char is the order for mvaddch()
	mvaddch(applePos[1], applePos[0] * 2, chars[1]); //prints apple, offset by spaces in columns
	
	mvaddch(snakePos[0][1], snakePos[0][0] * 2, chars[2]); //prints snake head, offset by spaces in columns

	for(int s = 1; s < *lengthPointer; s++) //annoyingly, I need to start the loop at 1 to make it more concise
	{
		mvaddch(snakePos[s][1], snakePos[s][0] * 2, chars[3]);
	}

	mvaddch(dims[1] - 1, dims[0] * 2 - 1, '\n'); //moves cursor to bottom of screen
	refresh();
}

void growSnake(int (*snakePos)[2], int *p)
{
	//remember to put the apple where the snake is NOT (iterate over all snake[s])
}

void printCurrentSnake(int (*snakePos)[2], int *p)
{
	for(int s = 0; s < *p; s++)
	{
		printf("Pos. %d: (%d, %d)\n", s, snakePos[s][0], snakePos[s][1]);
	}
}

void delayUntilNextFrame(clock_t frameStart, int framesPerSecond)
{
	float timePerFrame = (1.0 / (float)framesPerSecond);
	int milliDelay = (int)(timePerFrame * 1000);
	#ifdef _WIN32
		Sleep(milliDelay);
	#else
			usleep(1000 * milliDelay); //usleep uses microseconds
	#endif
}

void updateGameState(bool isFirstRun)
{
	if(isFirstRun)
	{
		//continue to execute
		isFirstRun = false;
	}
}

//
//BEGIN PROGRAM
//

int main(int *argc, char **argv)
{	
	int framesPerSecond = 1;

	bool gameLoopActive = true;
	bool isFirstRun = true;

	int screenSize[2] = {11, 11}; //magic number
	char charArray[4] = {'+', '@', 'O', 'o'};

	int currentLength = 1;
	int *lengthPointer;
	lengthPointer = &currentLength;

	int (*snakePos)[2];
	int applePos[2] = {3, 3}; //magic number

	snakePos = calloc(1, 2 * sizeof(int));
	snakePos[0][0] = 5; //maaagic
	snakePos[0][1] = 5; //nuuumbers
	
	
	while(gameLoopActive)
	{
		clock_t frameStart = clock();
		
		initscr(); //start curses mode
		cbreak(); //line buffering disabled, also allows interrupts
		keypad(stdscr, TRUE);  //get the fun keys like F1
		noecho(); //do not echo when getch() is called

		updateGameState(isFirstRun);
		
	//	printGrid(applePos, snakePos, screenSize, charArray, lengthPointer);
	
		int random = rand();
		printw("%d", random);
		refresh();

		delayUntilNextFrame(frameStart, framesPerSecond);
		
		//printCurrentSnake(snakePos, lengthPointer);
		//growSnake(snakePos, lengthPointer);
		//printCurrentSnake(snakePos, lengthPointer);
		//printf("~\n");
		clear();
		refresh();
	}
	endwin();
	free(snakePos);
	return 0;
}
