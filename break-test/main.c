#include <stdio.h>

int main(int argc, char **argv)
{
	int appleX = 4;
	int appleY = 5;

	int snekX[10] = {0,1,2,3,4,5,6,7,8,9};
	int snekY[10] = {1,2,3,4,5,6,7,8,9,0};
	//collision is expected on the 5th iteration of the outside for loop
	while(1){
	printf("Beginning for loop!\n");
	for(int i = 0; i < 10; i++)
	{
		printf("i is currently %d\n", i);
		if(appleX == snekX[i] && appleY == snekY[i])
		{
			printf("\n\nCollision detected at (%d, %d)\n\n", appleX, appleY);
			break;
		}
		else
		{
			printf("No collide. a: %d %d  s: %d %d \n", appleX, appleY, snekX[i], snekY[i]);
		}
	}
}
}
//IT WORKS!
