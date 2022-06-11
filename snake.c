#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void delay(int seconds)
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
    #ifdef _WIN32
        Sleep(1000 * seconds);
    #else
        sleep(seconds);
    #endif
}
 
// Driver code to test above function
int main(int argc, char **argv)
{
	int i;
	for (i = 0; i < 10; i++)
	{
        	// delay of one second
        	delay(1);
        	printf("%d seconds have passed\n", i + 1);
    	}
    return 0;
}
