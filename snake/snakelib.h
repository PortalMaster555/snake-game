#ifndef SNAKELIB_DOT_H
#define SNAKELIB_DOT_H

#define SCREEN_SIZE 9

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
void printGrid(grid grid, snake snake, apple apple);

snake initSnake(int startX, int startY);
apple initApple(grid grid, snake snake);

int checkGameOver(grid grid, snake snake);

snake moveSnake(snake snake);


#endif
