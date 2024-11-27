#include "Food.h"
#include <time.h>
#include <stdlib.h>

Food::Food()
{
	foodPos = objPos(6, 8, '@');
	// foodPos.symbol = '@';
}

Food::~Food()
{
 // Not needed
}

void Food::generateFood(objPos blockOff)
{	
	bool flag = true;
	while (flag){
		foodPos.pos->x = rand() % (30 - 2) + 1;
		foodPos.pos->y = rand() % (15 - 2) + 1;
		if((blockOff.pos->x == foodPos.pos->x) && (blockOff.pos->y == foodPos.pos->y)){
			flag = true;
			break;
		}
		else{
			flag = false;
		}
	}
	// generate random food x and y positions
	// we can simply use one symbol for the food
	// if the player x and player y = the food x and food y, continue
	// no need for a for loop since we are only generating one character
}

objPos Food::getFoodPos() const
{
	return foodPos;
}