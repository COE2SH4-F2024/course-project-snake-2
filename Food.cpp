#include "Food.h"

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

	while (flag)
	{
		foodPos.pos->x = rand() % (30 - 2) + 1;
		foodPos.pos->y = rand() % (15 - 2) + 1;

		if (blockOff.pos->x == foodPos.pos->x && blockOff.pos->y == foodPos.pos->y)
			break;
		else
			flag = false;
	}
}

objPos Food::getFoodPos() const
{
	return foodPos;
}