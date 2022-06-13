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
	
	snakePos = malloc(currentLength * 2);
	snakePosStorage = malloc(currentLength * 2);

	snakePos[0][0] = 2;
	snakePos[0][1] = 3;

	memcpy(snakePosStorage, snakePos, sizeof(snakePos)); 
	free(snakePos);	
	for(int i = 0; i < 5; i++)
	{	
		memcpy(snakePos, snakePosStorage, sizeof(snakePos));

		for(int s = 0; s < currentLength; s++)
		{
			printf("(%d, %d)\n", snakePos[s][0], snakePos[s][1]);	
		}
		printf("\n");
	
		snakePosStorage = malloc((currentLength + 1) * 2);
		memcpy(snakePosStorage, snakePos, sizeof(snakePos)); //the snake now has an extra [x,y] set to use
				currentLength++;
		free(snakePos);
	}
	return 0;
}
