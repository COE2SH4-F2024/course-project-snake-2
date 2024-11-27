#include "Food.h"

Food::Food()
{
	foodPos = objPos();
}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{

}

objPos Food::getFoodPos() const
{
	return foodPos;
}