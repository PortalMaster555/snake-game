#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

float framesPerSecond = 60;
int screenX = 11;
int screenY = 11;

char bgChar = '.';
char snakeHeadChar = 'O';
char snakeBodyChar = 'o';
char appleChar = '@';

bool gameLoop = false;

#define MAX_SNAKE_LENGTH 100
int snakePos[MAX_SNAKE_LENGTH][2];
int applePos[2] = {5, 5};

//TIME FUNCTION
void delay(float seconds)
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
	int milliSeconds = 1000 * seconds;
	#ifdef _WIN32
		Sleep(milliSeconds);
    #else
        usleep(1000 * milliSeconds); //usleep uses microseconds
	#endif
}

//GAME FUNCTIONS

int isSnakeHead(int currentCoord[2], int snakePos[100][2])
{
	for(int sx = 0; sx < MAX_SNAKE_LENGTH; sx++)
	{
		if(memcmp(currentCoord, snakePos[sx], 2) == 0)
		{
			printf("%d", sx);
			return 1;
		}
	}
	return 0;
}

int isSnakeBody(int currentCoord[2], int snakePos[100][2])
{
	return 0;	
}

void printGrid(int screenX, int screenY, int snakePos[100][2], int applePos[2])
{
	for(int y = 0; y < screenY; y++)
	{
		for(int x = 0; x < screenX; x++)
		{
			int currentCoord[2] = {x, y};
			if(memcmp(currentCoord, applePos, sizeof(currentCoord)) == 0) //purified awful, checks if arrays are identical
			{
				printf("%c ", appleChar);
			}
			else if(isSnakeHead(currentCoord, snakePos))
			{
				printf("%c ", snakeHeadChar);
			}
			else if(isSnakeBody(currentCoord, snakePos))
			{
				printf("%c ", snakeBodyChar);
			}
			else
			{
				printf("%c ", bgChar);
			}
		}
		printf("\n");
	}
}

//
//	BEGIN PROGRAM
//
int main(int argc, char **argv)
{
	snakePos[0][0] = 2;
	snakePos[0][1] = 2;
	printGrid(screenX, screenY, snakePos, applePos);
	delay(1.0 / framesPerSecond);
	
	return 0;
}
