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

void checkDebugKey(int debugKey, bool *isDebugEnabled)
{
	int ch = getch();
	if(ch == debugKey)
	{
		*isDebugEnabled = !*isDebugEnabled;
	}
}

void writeDebugMenu(bool *isDebugEnabled, int applePos[2], int (*snakePos)[2], int *lengthPointer, char *direction)
{
	if(*isDebugEnabled)
	{
		int maxX, maxY;
		getmaxyx(stdscr, maxY, maxX);
		maxY--;
		maxX--;

		mvprintw(maxY - 3, 0, "Current Direction: %s", direction);

		mvprintw(maxY - 2, 0, "A:(%d, %d)", applePos[0], applePos[1]);
		for(int i = 0; i < *lengthPointer; i++)
		{	
			mvprintw(maxY - 1, 0, "%d:(%d, %d) ", i, snakePos[i][0], snakePos[i][1]); 
		}

		mvprintw(maxY, 0, "Current Snake Length: %d", *lengthPointer);

		refresh();
	}
}

char* setMovement(int snakeDir[2], int controls[8])
{ // L R S , D U S
	int key = getch();
	if(key == controls[0] || key == controls[4])
	{
		snakeDir[0] = 0;
		snakeDir[1] = 1;
		return "UP   ";
	}
	else if(key == controls[1] || key == controls[5])
	{
		snakeDir[0] = -1;
		snakeDir[1] = 0;
		return "LEFT ";
	}
	else if(key == controls[2] || key == controls[6])
	{
		snakeDir[0] = 0;
		snakeDir[1] = -1;
		return "DOWN ";
	}
	else if(key == controls[3] || key == controls[7])
	{
		snakeDir[0] = 1;
		snakeDir[1] = 0;
		return "RIGHT";
	}
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
	bool *debugStatusPointer = &isDebugEnabled;
	int debugKey = KEY_F(3);

	initscr(); //activate curses mode
	cbreak(); //line buffering disabled, also allows interrupts
	keypad(stdscr, TRUE);  //get the fun keys like F1
	noecho(); //do not echo when getch() is called
	nodelay(stdscr, TRUE);

	placeApple(applePos, snakePos, lengthPointer, screenSize);
	
	int snakeDir[2] = {-1, 0}; // X: -1 = LEFT, 1 = RIGHT, 0 = STATIONARY
								// Y: -1 = DOWN, 1 = UP, 0 = STATIONARY

	int controls[8] = {'w', 'a', 's', 'd', KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT};

	while(gameLoopActive)
	{
		clock_t frameStart = clock();

		updateGameState(isFirstRun);
		
		printGrid(applePos, snakePos, screenSize, charArray, lengthPointer);
		char *direction = calloc(1, 5 * sizeof(char));
	//	direction = setMovement(snakeDir, controls);

		checkDebugKey(debugKey, debugStatusPointer);
		writeDebugMenu(debugStatusPointer, applePos, snakePos, lengthPointer, direction);
		
		free(direction);

		flushinp(); //flush unprocessed inputs from repeated keystrokes
		delayUntilNextFrame(frameStart, framesPerSecond);
		clear();
		refresh();
	}
	endwin();
	free(snakePos);
	return 0;
}
