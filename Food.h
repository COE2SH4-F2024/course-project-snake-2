#ifndef FOOD_H
#define FOOD_H

#include <stdlib.h>
#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
	private:
		objPos foodPos;

	public:
		Food();
		~Food();

		void generateFood(objPosArrayList* blockOff);
		objPos getFoodPos() const;
};

#endif