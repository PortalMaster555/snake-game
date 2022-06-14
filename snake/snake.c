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

void placeApple(int applePos[2], int (*snakePos)[2], int *lengthPtr, int screenSize[2])
	//this will continuously execute until it is able to place the apple on a different spot than the snake.
{
	applePos[0] = rand() % screenSize[0];
	applePos[1] = rand() % screenSize[1];

	for(int i = 0; i < *lengthPtr; i++){
		while (memcmp(applePos, snakePos[i], 8) == 0) //applePos size guaranteed to be 8 bytes
		{
			applePos[0] = rand() % screenSize[0];
			applePos[1] = rand() % screenSize[1];
		}
	}
}

//

void printGrid(int applePos[2], int (*snakePos)[2], int dims[2], char chars[4], int *lengthPointer)
{ //chars are + @ O o
	for(int y = 0; y < dims[1]; y++)
	{
		for(int x = 0; x < dims[0]; x++)
		{
			mvaddch(y, x * 2, chars[0]);
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

//

void printCurrentSnake(int (*snakePos)[2], int *p)
{
	for(int s = 0; s < *p; s++)
	{
		printf("Pos. %d: (%d, %d)\n", s, snakePos[s][0], snakePos[s][1]);
	}
}

//

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

//

void updateGameState(bool isFirstRun)
{
	if(isFirstRun)
	{
		//continue to execute
		isFirstRun = false;
	}
}

void writeDebugMenu(); //compiler has a heart attack because of implicit declaration in checkDebugKey()

void checkDebugKey(int debugKey, bool *isDebugEnabled, int applePos[2], int (*snakePos)[2], int *lengthPointer)
{
	int ch = getch();
	if(ch == debugKey)
	{
		*isDebugEnabled = !*isDebugEnabled;
	}
	writeDebugMenu(isDebugEnabled, applePos, snakePos, lengthPointer);
}

void writeDebugMenu(bool *isDebugEnabled, int applePos[2], int (*snakePos)[2], int *lengthPointer)
{
	if(*isDebugEnabled)
	{
		mvprintw(30, 5, "A:(%d, %d)", applePos[0], applePos[1]);
		for(int i = 0; i < *lengthPointer; i++)
		{	
			mvprintw(31, 5, "%d:(%d, %d) ", i, snakePos[i][0], snakePos[i][1]);
		}
		refresh();
	}
	flushinp(); //flush unprocessed inputs from repeated keystrokes
}

//
//BEGIN PROGRAM
//

int main(int *argc, char **argv)
{
	srand(time(NULL)); //init random seed based on UNIX time

	int framesPerSecond = 1;

	bool gameLoopActive = true;
	bool isFirstRun = true;

	int screenSize[2] = {11, 11};

	char charArray[4] = {'+', '@', 'O', 'o'};

	int currentLength = 1;
	int *lengthPointer;
	lengthPointer = &currentLength;


	int (*snakePos)[2];
	
	snakePos = calloc(1, 2 * sizeof(int));
	snakePos[0][0] = screenSize[0] / 2; //integer division makes finding
	snakePos[0][1] = screenSize[1] / 2; //the center convenient
	
	int applePos[2] = {0, 0};
	
	//DEBUG
	bool isDebugEnabled = false;
	bool *debugStatPoint = &isDebugEnabled;
	int debugKey = KEY_F(3);

	initscr(); //activate curses mode
	cbreak(); //line buffering disabled, also allows interrupts
	keypad(stdscr, TRUE);  //get the fun keys like F1
	noecho(); //do not echo when getch() is called
	nodelay(stdscr, TRUE);

	placeApple(applePos, snakePos, lengthPointer, screenSize);
	while(gameLoopActive)
	{
		clock_t frameStart = clock();
		placeApple(applePos, snakePos, lengthPointer, screenSize);

		updateGameState(isFirstRun);
		
		printGrid(applePos, snakePos, screenSize, charArray, lengthPointer);
	
		checkDebugKey(debugKey, debugStatPoint, applePos, snakePos, lengthPointer);
		
		delayUntilNextFrame(frameStart, framesPerSecond);
		
		//printCurrentSnake(snakePos, lengthPointer);
		//printf("~\n");
		clear();
		refresh();
	}
	endwin();
	free(snakePos);
	return 0;
}
