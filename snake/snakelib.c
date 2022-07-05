#include "snakelib.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>

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

snake initSnake(int startX, int startY)
{
	snake snake;
	snake.xPtr = malloc(sizeof(int));
	*snake.xPtr = startX;
	snake.yPtr = malloc(sizeof(int));
	*snake.yPtr = startY;
	snake.length = 1;
	snake.direction = 'L';
	return snake;
}

void initApple(snake snake)
{
	
}
