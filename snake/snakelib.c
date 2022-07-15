#include "snakelib.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h> //for memcpy

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
			mvprintw(y, x * 2, "%c", gameChars[0]); //x * 2 balances with line height on my machine
			
			if(x == apple.x && y == apple.y)
			{
				mvprintw(y, x * 2, "%c", gameChars[3]);
			}

			for(int i = 0; i < (snake.length); i++)
			{
				if(x == snake.xPtr[i] && y == snake.yPtr[i])
				{
					if(i == 0)
						mvprintw(y, x * 2, "%c", gameChars[1]);
					else
						mvprintw(y, x * 2, "%c", gameChars[2]);
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

int checkGameOver(grid grid, snake snake)
{
	return 0;
}

snake snakeGrow(snake snake)
{
	snake.length++;
	snake.xPtr = realloc(snake.xPtr, snake.length * sizeof(int) + 1); //why does adding an extra byte fix it?
	snake.xPtr[snake.length - 1] = 0;
	snake.yPtr = realloc(snake.yPtr, snake.length * sizeof(int) + 1); //i will choose to not worry about it.
	snake.yPtr[snake.length - 1] = 0;
	return snake;
}

snake snakeShift(snake snake)
{
	//for(int i = 1; i < snake.length; i++)
	for(int i = snake.length; i > 0; i--)	
	{
		snake.xPtr[i] = snake.xPtr[i - 1];
		snake.yPtr[i] = snake.yPtr[i - 1];
	}

	switch(snake.direction)
	{
		case 'U':
			(*snake.yPtr)--;
			break;
		case 'L':
			(*snake.xPtr)--;
			break;
		case 'D':
			(*snake.yPtr)++;
			break;
		case 'R':
			(*snake.xPtr)++;
			break;
	}
	return snake;
}
