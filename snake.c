#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

//FUNCTIONS

void printGrid()
{
	
}

//VARIABLES



//
//BEGIN PROGRAM
//

int main(int *argc, char **argv)
{
	bool isGameOver = false;
	int currentLength = 1;

	int applePos[2] = {0, 0};
	int (*snakePos)[2];
	int (*snakePosStorage)[2];
	
	snakePos = (int(*)[2])malloc(currentLength * 2);

	snakePos[0][0] = 42069;
	snakePos[0][1] = 69420;

	for(int i = 0; i < 5; i++)
	{
		for(int s = 0; s < currentLength; s++)
		{
			printf("Pos. %d: (%d, %d)", s, snakePos[s][0], snakePos[s][1]);
		}
		printf("\n");
	}
	return 0;
}
