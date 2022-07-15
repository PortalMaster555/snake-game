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
    nodelay(stdscr, TRUE);
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
	snake.xPtr = realloc(snake.xPtr, snake.length * sizeof(int) + 1);
	snake.xPtr[snake.length - 1] = 0;
	snake.yPtr = realloc(snake.yPtr, snake.length * sizeof(int) + 1);
	snake.yPtr[snake.length - 1] = 0;
	return snake;
}

snake snakeShift(snake snake, grid grid)
{
	for(int i = snake.length; i > 0; i--)	
	{
		snake.xPtr[i] = snake.xPtr[i - 1];
		snake.yPtr[i] = snake.yPtr[i - 1];
	}

	switch(snake.direction)
	{
		case 'U':
			(*snake.yPtr)--;
			if(*snake.yPtr < 0)
				*snake.yPtr = grid.ydim - 1; //LOOP
				//gameover code can be here in all 4 instead
			break;
		case 'L':
			(*snake.xPtr)--;
			if(*snake.xPtr < 0)
				*snake.xPtr = grid.xdim - 1; //LOOP
			break;
		case 'D':
			(*snake.yPtr)++;
			if(*snake.yPtr >= grid.ydim) //LOOP
				*snake.yPtr = 0;
			break;
		case 'R':
			(*snake.xPtr)++;
			if(*snake.xPtr >= grid.ydim) //LOOP
				*snake.xPtr = 0;
			break;
	}
	return snake;
}


char takeInput(char isDebugEnabled, snake snake)
{
	int ch;
	ch = getch();
	
	switch(ch)
	{
		case 'w': case KEY_UP:
			if(snake.direction != 'D')
			{
				mvprintw(11, 3, "UP");
				return 'U';
			}
			break;
		case 'a': case KEY_LEFT:
			if(snake.direction != 'R')
			{
				mvprintw(11, 3, "LEFT");
				return 'L';
			}
			break;
		case 's': case KEY_DOWN:
			if(snake.direction != 'U')
			{
				mvprintw(11, 3, "DOWN");
				return 'D';
			}
			break;
		case 'd': case KEY_RIGHT:
			if(snake.direction != 'L')
			{
				mvprintw(11, 3, "RIGHT");
				return 'R';
			}
			break;
		case KEY_F(3):
			return 'M'; //M for debug [M]enu
		default:
			return '\0';
	}
}

void printDebug(char input, char isDebugEnabled, snake snake)
{
    if(isDebugEnabled) //DEBUG MENU
    {
		mvprintw(15, 5, "Debug is enabled!");
		for(int i = 0; i < snake.length; i++)
        {
			mvprintw(16 + i, 5, "X: %d, Y: %d", snake.xPtr[i], snake.yPtr[i]);
    	}
    }
}

apple checkAppleCollisions(int *score, snake snake, apple apple, grid grid)
{
	for(int i = 0; i < snake.length; i++)
	{
		if(*snake.xPtr == apple.x && *snake.yPtr == apple.y)
		{
			*score++;
			apple = initApple(grid, snake);
		}
	}
	return apple;
}
