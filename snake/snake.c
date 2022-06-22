#include <stdio.h>


int num = 5;

void incrementNum(void)
{
	++num;
}

int main(int argc, char **argv)
{
	printf("The integer is %d\n", num);
	incrementNum();
	printf("The integer is %d\n", num);
}


