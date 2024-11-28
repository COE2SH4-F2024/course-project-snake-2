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

void Food::generateFood(objPosArrayList* blockOff)
{	
	bool flag = true;

	while (flag)
	{
		foodPos.pos->x = rand() % (30 - 2) + 1;
		foodPos.pos->y = rand() % (15 - 2) + 1;

		for (int i = 0; i < blockOff->getSize(); i++)
		{
			objPos bodyPart = blockOff->getElement(i);

			if (bodyPart.pos->x == foodPos.pos->x && bodyPart.pos->y == foodPos.pos->y)
				break;
			else
				flag = false;
		}
	}
}

objPos Food::getFoodPos() const
{
	return foodPos;
}