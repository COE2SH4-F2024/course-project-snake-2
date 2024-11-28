#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Food
{
	private:
		objPosArrayList* foodBucket;

		GameMechs* mainGameMechsRef;

	public:
		Food(GameMechs* thisGMRef);
		~Food();

		void generateFood(objPosArrayList* blockOff);
		objPosArrayList* getFoodPos() const;
};

#endif