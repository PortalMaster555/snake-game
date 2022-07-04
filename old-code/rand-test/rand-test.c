#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h> //for rand()
#include <time.h>


#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

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

int main(int *argc, char **argv)
{
	int randNum;
	int modRand;

	int counter[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	int framesPerSecond = 60;

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	while(true)
	{
		clock_t frameStart = clock();

		clear();
		randNum = rand();
		modRand = randNum % 11;
		counter[modRand]++;
		printw("The random number is %d, which maps down to %d. ", randNum, modRand);
		for(int i = 0; i < 11; i++)
		{
			printw("\n%d: %d ", i, counter[i]);
		}
		refresh();
		//delayUntilNextFrame(frameStart, framesPerSecond);
	}
}

//the results here indicate that a simple naive modulo to reduce the range of rand() is good enough for my purposes.
