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
	int *applePos;
	applePos = (int*)malloc(2 * sizeof(int));
	
	printf("(%d, %d) allocated, later turns into ", applePos[0], applePos[1]);

	int newApplePos[2] = {0, 1};

	memcpy(applePos, newApplePos, sizeof(applePos));

	printf("(%d, %d)\n", applePos[0], applePos[1]);
	return 0;
}
