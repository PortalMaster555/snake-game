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
	char isCollided;
} snake;

typedef struct
{
	int x;
	int y;
	char isPlaceable;
} apple;


void initCursesEnv(void);
void delay(int millis);
void printGrid(grid grid, snake snake, apple apple);

snake initSnake(int startX, int startY);
apple initApple(apple apple, grid grid, snake snake);

int checkGameOver(grid grid, snake snake);

snake snakeGrow(snake snake, grid grid);
snake snakeShift(snake snake, grid grid);

char takeInput(char isDebugEnabled, snake snake);
void printDebug(char input, char isDebugEnabled, snake snake, apple apple);

int checkAppleCollisions(snake snake, apple apple);
#endif
