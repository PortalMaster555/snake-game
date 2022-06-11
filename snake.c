#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

float framesPerSecond = 60;

void delay(float seconds)
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
    int milliSeconds = 1000 * seconds;
	#ifdef _WIN32
        	Sleep(milliSeconds);
    	#else
        	usleep(1000 * milliSeconds); //usleep uses microseconds
	#endif
}
 
int main(int argc, char **argv)
{
	int i;
	for (i = 0; i < 360; i++)
	{
		printf("%f: ", 1.0 / framesPerSecond);
        	delay(1.0 / framesPerSecond);
        	printf("Frame %d\n", i + 1);
    	}
    return 0;
}
