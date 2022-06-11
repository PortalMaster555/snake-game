#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

float framesPerSecond = 60;
int screenX = 10
int screenY = 10

bool gameLoop = false;

int **snakePos;
int *applePos;

int main(int argc, char **argv)
{
	gameLoop = true;
	while(gameLoop)
	{
        	delay(1.0 / framesPerSecond);
	}
    return 0;
}

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

void printGrid(snakePos, applePos
