#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include <unistd.h>

//FUNCTION DECLARATIONS

void activateWindowEnv(void); //runs ncurses
void printGrid(void);
void delayToFrame(struct timespec start, struct timespec end); //delays until next frame
void actOnInputs(void);
void printDebug(void);
void setSnakeDir(char key); //takes in pressed key and changes dir. accordingly
void placeRandApple(void);

//VARIABLES
int isGameplay = 0; //game is initially not in motion
int isDebug = 0; //no debug menu shown

int charSet[] = {'w', 'a', 's', 'd', KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_F(3), ' '}; //spacebar at end
																		float framesPerSecond = 1.0;
		
																		struct timespec start, end;

int64_t diff;

//BEGIN PROGRAM
int main(int argc, char **argv)
{
	activateWindowEnv();
	//nothing above this point
	isGameplay = 1;
	
	clock_gettime(CLOCK_MONOTONIC, &start);
	clock_gettime(CLOCK_MONOTONIC, &end);
	end.tv_sec = start.tv_sec + 1;
	end.tv_nsec = 0;	//initial values to make first frame work
	
	while(isGameplay)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);	
		printGrid();
		//actOnInputs();
		//getch();
		(isDebug == 0) ? : printDebug(); //if isDebug, printDebug
		
		flushinp();
		refresh();
		
		delayToFrame(start, end); //takes up the rest of frame time
		clear();
		clock_gettime(CLOCK_MONOTONIC, &end);
		diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
		
		long long unsigned microSeconds = diff / 1000; 
		printw("Start: %llu, End: %llu\n", (long long unsigned) start.tv_nsec, (long long unsigned) end.tv_nsec);
		printw("Delay in microseconds: %llu \n", microSeconds);
		refresh();


	}

	//nothing below this point
	endwin();
	return 0;
}

//FUNCTION DEFINITIONS

void activateWindowEnv(void)
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
//	nodelay(stdscr, TRUE);
}

void printGrid(void)
{}

void delayToFrame(struct timespec start, struct timespec end)
{
	float timePerFrame = 1.0 / framesPerSecond;
	int milliDelay = (int)(timePerFrame * 1000);
	int microDelay = milliDelay * 1000;
	usleep(microDelay);
}

void actOnInputs(void)
{
	int ch = getch();
	switch(ch)
	{
		case 'w': case KEY_UP: //i hate this
			printw("UP");
	}
}

void printDebug(void)
{}

void setSnakeDir(char key)
{}

void placeRandApple(void)
{}
