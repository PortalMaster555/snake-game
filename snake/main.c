#include <stdio.h>
#include <ncurses.h>

int main(int argc, char **argv)
{
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	//nodelay(stdscr, TRUE);

	printw("Hello, world!\n");
	getch();

	endwin();
	return 0;
}
