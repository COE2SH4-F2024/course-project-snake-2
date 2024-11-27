#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
	aList = new objPos[ARRAY_MAX_CAP];
	listSize = 0;
	arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
	delete[] aList;
}

int objPosArrayList::getSize() const
{
	return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
	// DO NOT insert anything if arrayCapacity is reached
	if (listSize >= arrayCapacity) return;

	for (int i = listSize; i > 0; i--)
		aList[i] = aList[i - 1];

	aList[0] = thisPos;
	listSize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
	// DO NOT insert anything if arrayCapacity is reached
    if (listSize >= arrayCapacity) return;

	aList[listSize++] = thisPos;
}

void objPosArrayList::removeHead()
{
    // DO NOT remove anything listSize = 0
	if (listSize == 0) return;

	for (int i = 0; i < listSize - 1; i++)
		aList[i] = aList[i + 1];
	
	listSize--;
}

void objPosArrayList::removeTail()
{
	if (listSize > 0)
		listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
	// Check if out-of-bounds
	if (index < 0) index = 0;
	else if (index >= arrayCapacity) index = arrayCapacity - 1;
	
	return aList[index];
}