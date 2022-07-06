#include "snakelib.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>


extern char gameChars[4];

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

void printGrid(grid grid, snake snake, apple apple)
{
	for(int y = 0; y < grid.ydim; y++)
	{
		for(int x = 0; x < grid.xdim; x++)
		{
			for(int i = 0; i < (snake.length); i++)
			{
				if(x == snake.xPtr[i] && y == snake.yPtr[i])
				{
					if(i == 0)
						mvprintw(y, x * 2, "%c", gameChars[1]);
					else
						mvprintw(y, x * 2, "%c", gameChars[2]);
				}
				else if(x == apple.x && y == apple.y)
				{
					mvprintw(y, x * 2, "%c", gameChars[3]);
				}
				else
				{
					mvprintw(y, x * 2, "%c", gameChars[0]); //x * 2 balances with line height on my machine
				}
			}
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

apple initApple(grid gameGrid, snake snake)
{
	apple apple;
	int attempts = 0;
	while(1) //loop until success
	{
		char isConflict = 0;
		apple.x = rand() % gameGrid.xdim;
		apple.y = rand() % gameGrid.ydim;

		for(int i = 0; i < snake.length; i++)
		{
			if(apple.x == *snake.xPtr && apple.y == *snake.yPtr)
			{
				isConflict = 1;
				//mvprintw(12 + attempts, 12 + attempts, "CLANG!");	
				break;
			}
		}
		if(!isConflict)
		{
			return apple; //return if no conflicts
		}
	}

}
