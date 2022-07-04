#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#include "snakelib.h"

int main(int argc, char **argv)
{
	initCursesEnv(); //boilerplate stuff to get ncurses to work

	int i = 0;
	while(1)
	{
		printw("%d\n", i++);
		refresh();
		delay(1000);
	}	

	getch();
	endwin();
	return 0;
}
