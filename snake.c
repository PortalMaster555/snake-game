#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
  	#include <windows.h>
#else
  	#include <unistd.h>
#endif

//FUNCTIONS

void printGrid(int applePos[2], int (*snakePos)[2], int dims[2], char chars[4])
{ //chars are . @ O o
	for(int y = 0; y < dims[1]; y++)
	{
		for(int x = 0; x < dims[0]; x++)
		{
				if(x == applePos[0] && y == applePos[1])
				{
					printf("%c ", chars[1]);
				}
				else if(x == snakePos[0][0] && y == snakePos[0][1])
				{
					printf("%c ", chars[2]);
				}
				else //nested ifs are disgusting
				{	
					bool isPrinted = false;
					for(int s = 0; s < sizeof(snakePos) / 2; s++)
					{
						if(x == snakePos[s][0] && y == snakePos[s][1] && !isPrinted)
						{
							
							printf("%c ", chars[3]);
							isPrinted = true;
						}
						else if(!isPrinted)
						{
							printf("%c ", chars[0]);
							isPrinted = true;
						}
					}
				}
		}
		printf("\n");
	}
}

void growSnake(int (*snakePos)[2], int *p)
{
		printf("\n");
		*p = *p + 1;
		snakePos = realloc(snakePos, *p * 2 * sizeof(int));
		snakePos[*p - 1][0] = *p;
		snakePos[*p - 1][1] = *p;
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

void updateGameState()
{
	
}

//
//BEGIN PROGRAM
//

int main(int *argc, char **argv)
{	
	int framesPerSecond = 1;

	bool gameLoopActive = true;

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
		
		updateGameState();
		
		printGrid(applePos, snakePos, screenSize, charArray);
		printf("\n");
		
		delayUntilNextFrame(frameStart, framesPerSecond);

		//growSnake(snakePos, lengthPointer);
		//printCurrentSnake(snakePos, lengthPointer);
	}
	free(snakePos);
	return 0;
}
