#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
	int applePos[2] = {0, 0};

	//memcpy(applePos, newApplePos, sizeof(applePos));

	printf("(%d, %d)\n", applePos[0], applePos[1]);
	return 0;
}
