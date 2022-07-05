#ifndef SNAKELIB_DOT_H
#define SNAKELIB_DOT_H

#define SCREEN_SIZE 11

typedef struct 
{
	int xdim;
	int ydim;
} grid;

typedef struct
{
	int *xPtr;
	int *yPtr;
	int length;
	char direction;
} snake;

typedef struct
{
	int x;
	int y;
} apple;

void initCursesEnv(void);
void delay(int millis);
void printGrid(grid grid);
snake initSnake(int startX, int startY);
void initApple(snake snake);
#endif
