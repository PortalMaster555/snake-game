#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#include "snakelib.h"

int main(int argc, char **argv)
{
	initCursesEnv(); //boilerplate stuff to get ncurses to work

	grid gameGrid = {SCREEN_SIZE, SCREEN_SIZE}; // alter definition if needed

	int isGameplay = 1;
	while(isGameplay) //main game loop
	{
		printGrid(gameGrid);
		




		refresh();
		delay(1000); //1 second plus calculation time per frame, because implementing the necessary code to make a frame a fixed length of time is beyond the scope of this project
	}	

	getch();
	endwin();
	return 0;
}
