#include <stdio.h>
#include <ncurses.h>

#include "snakelib.h"

int main(int argc, char **argv)
{
	initCursesEnv();

	printw("Hello, world!\n");
	getch();

	endwin();
	return 0;
}
