#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

//FUNCTIONS

//VARIABLES

//
//BEGIN PROGRAM
//

int main(int *argc, char **argv)
{
	printf("Hello, world!");	
	return 0;
}
