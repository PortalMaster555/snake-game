#include <stdio.h>

int isTrue = 1;

int main(int argc, char **argv)
{
	while(1)
	{
		isTrue = !isTrue;
		printf("%d", isTrue);
	}
}
