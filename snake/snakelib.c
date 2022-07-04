#include "snakelib.h"

#include <ncurses.h>
#include <unistd.h>

void initCursesEnv(void)
{
	initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    //nodelay(stdscr, TRUE);
}

void delay(int millis)
{
	usleep(millis * 1000);
}

void printGrid(grid grid)
{
	for(int y = 0; y < grid.ydim; y++)
	{
		for(int x = 0; x < grid.xdim; x++)
		{
			mvprintw(y, x * 2, "+"); //x * 2 balances with line height
		}
	}
}
