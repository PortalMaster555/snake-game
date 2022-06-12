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

int snakePos[100][2];
int applePos[2] = {4, 4};

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

void printGrid(int screenX, int screenY, int snakePos[100][2], int applePos[2])
{
	for(int y = 0; y < screenY; y++)
	{
		for(int x = 0; x < screenX; x++)
		{
			if(x != applePos[0] || y != applePos[1])
			{
				printf("%c ", bgChar);
			}
			else
			{
				printf("%c ", appleChar);
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
	//applePos[0] = screenX / 2;
	//applePos[1] = screenY / 2;

	gameLoop = true;
	//while(gameLoop)
	//{
		printGrid(screenX, screenY, snakePos, applePos);
        	delay(1.0 / framesPerSecond);
	//}
	
	

	return 0;
}
