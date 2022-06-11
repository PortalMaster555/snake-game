#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

float framesPerSecond = 60;
int screenX = 10;
int screenY = 10;

char bgChar = '.';
char snakeHeadChar = 'O';
char snakeBodyChar = 'o';
char appleChar = '@';

bool gameLoop = false;

int **snakePos;
int *applePos;

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

//(int **snakePos, int *applePos) *add* these to below
void printGrid(int screenX, int screenY)
{
	for(int y = 0; y < screenY; y++)
	{
		for(int x = 0; x < screenX; x++)
		{
			printf("%c ", bgChar);
		}
		printf("\n");
	}
}

//
//	BEGIN PROGRAM
//
int main(int argc, char **argv)
{
	gameLoop = true;
	//while(gameLoop)
	//{
		printGrid(screenX, screenY);
        	delay(1.0 / framesPerSecond);
	//}
	
	return 0;
}

