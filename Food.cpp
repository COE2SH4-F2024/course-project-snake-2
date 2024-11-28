#include "Food.h"

Food::Food(GameMechs* thisGMRef)
{
	mainGameMechsRef = thisGMRef;
	foodBucket = new objPosArrayList();
}

Food::~Food()
{
	delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{	
	int i = 0, j = 0, x = 0, y = 0;

	// Board size for item generation
	int xSize = mainGameMechsRef->getBoardSizeX() - 2;
	int ySize = mainGameMechsRef->getBoardSizeY() - 2;

	// Delete previous items
	for (j = foodBucket->getSize(); j > 0; j--)
		foodBucket->removeTail(); 

	while (i < 3)
	{
		x = rand() % xSize + 1;
		y = rand() % ySize + 1;

		// Checks if generated inside snake object
		for (j = 0; j < blockOff->getSize(); j++)
		{
			objPos bodyPart = blockOff->getElement(j);

			if (bodyPart.pos->x == x && bodyPart.pos->y == y)
				break;
		}

		// Checks if generated inside other food object
		for (j = 0; j < i; j++)
		{
			objPos foodPos = foodBucket->getElement(j);

			if (foodPos.pos->x == x && foodPos.pos->y)
				break;
		}

		if (i < 2)
			foodBucket->insertTail(objPos(x, y, '@'));
		else
			foodBucket->insertTail(objPos(x, y, '!'));

		i++;
	}
}

objPosArrayList* Food::getFoodPos() const
{
	return foodBucket;
}