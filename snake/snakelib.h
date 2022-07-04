#ifndef SNAKELIB_DOT_H
#define SNAKELIB_DOT_H

#define SCREEN_SIZE 11

typedef struct 
{
	int xdim;
	int ydim;
} grid;

void initCursesEnv(void);
void delay(int millis);
void printGrid(grid grid);

#endif
