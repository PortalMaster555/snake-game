#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include <unistd.h>

//FUNCTION DECLARATIONS

void activateWindowEnv(void); //runs ncurses
void printGrid(void);
void delayToFrame(struct timespec start, struct timespec end); //delays until next frame
															   //
void movementInputCalls(int ch);

void printDebug(void);

void setSnakeDir(char key); //takes in pressed key and changes dir. accordingly
void placeRandApple(void);

//VARIABLES
int isGameplay = 0; //game is initially not in motion
int isDebug = 1; // debug menu shown

int charSet[] = {'w', 'a', 's', 'd', KEY_UP, KEY_LEFT, KEY_DOWN, KEY_RIGHT, KEY_F(3), ' '}; //spacebar at end
																		float framesPerSecond = 1.0;
		
																		struct timespec start, end;

uint64_t diff = 0;

//BEGIN PROGRAM
int main(int argc, char **argv)
{
	activateWindowEnv();
	//nothing above this point
	isGameplay = 1;
	
	while(isGameplay)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);	
		printGrid();
		
		int ch = getch();

		(ch == KEY_F(3)) ? isDebug = !isDebug : movementInputCalls(ch); //if the key pressed is the debug key F3, toggle debug, otherwise check movement keys
		
		flushinp();
	
		delayToFrame(start, end); //takes up the rest of frame time
	
		clock_gettime(CLOCK_MONOTONIC, &end);

		(isDebug == 0) ? : printDebug(); //if isDebug, printDebug()	
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
	nodelay(stdscr, TRUE);
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

void movementInputCalls(int ch)
{
	switch(ch)
	{
		case 'w': case KEY_UP: //i hate this
			printw("UP\n");
			break;
		case 'a': case KEY_LEFT:
			printw("LEFT\n");
			break;
		case 's': case KEY_DOWN:
			printw("DOWN\n");
			break;
		case 'd': case KEY_RIGHT:
			printw("RIGHT\n");
			break;
	}
}

void printDebug(void)
{
	mvprintw(5, 0, "Debug goes here");
	
	diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	long long unsigned microSeconds = diff / 1000LLU; 
	printw("Start: %llu, End: %llu\n", (long long unsigned) start.tv_sec, (long long unsigned) end.tv_sec);
	printw("Delay in microseconds: %llu \n", microSeconds);
}


void setSnakeDir(char key)
{}

void placeRandApple(void)
{}
