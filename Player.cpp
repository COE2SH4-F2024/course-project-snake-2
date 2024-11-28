#include "Player.h"
#include <iostream>
#include "MacUILib.h"

using namespace std;

Player::Player(GameMechs* thisGMRef, Food* thisFDRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFDRef;
    playerPosList = new objPosArrayList();

    playerPosList->insertHead(objPos(15, 7, '*'));
    myDir = STOP;
}

Player::~Player()
{
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    return playerPosList;
}

bool Player::checkSelfCollision()
{
    bool collide = false;

    return collide;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    // Allows 90° turns, but not 180°
    switch(input)
    {
        case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        case 'a':
            if (myDir != RIGHT)
            {
            myDir = LEFT;
            }
            break;
        default:
            break;
    }
}

void Player::movePlayer()
{
    // Shortcuts
    int xMax = mainGameMechsRef->getBoardSizeX();
    int yMax = mainGameMechsRef->getBoardSizeY();
    int playerX = playerPosList->getHeadElement().pos->x;
    int playerY = playerPosList->getHeadElement().pos->y;
    
    // Storage variables
    int x = 0, y = 0;

    // Movement flag
    bool move = true;

    // Collision flag
    bool collide = false;
    
    // Movement implements wrap-around logic
    switch(myDir)
    {
        case UP:
            y = (playerY > 1) ? (playerY - 1) : (yMax - 2);
            x = playerX;
            break;
        case DOWN:
            y = (playerY < (yMax - 2)) ? (playerY + 1) : 1;
            x = playerX;
            break;
        case LEFT:
            x = (playerX > 1) ? (playerX - 1) : (xMax - 2);
            y = playerY;
            break;
        case RIGHT:
            x = (playerX < (xMax - 2)) ? (playerX + 1) : 1;
            y = playerY;
            break;
        default:
            move = false;
            break;
    }

    // Only start movement if myDir != STOP
    if (move)
    {
        // Check for collision with food
        for (int i = 0; i < mainFoodRef->getFoodPos()->getSize(); i++)
        {
            objPos singleFood = mainFoodRef->getFoodPos()->getElement(i);
            int foodX = singleFood.pos->x;
            int foodY = singleFood.pos->y;
            char foodSym = singleFood.getSymbol();

            if (playerX == foodX && playerY == foodY)
            {
                mainFoodRef->generateFood(playerPosList);

                if (foodSym == '@') // Increases size and score by 1
                    playerPosList->insertHead(objPos(x, y, '*'));
                else if (foodSym == '!') // Decreases size and score by 1
                    playerPosList->removeTail();

                int playerSize = playerPosList->getSize();

                // Update score
                if (playerSize > 0)
                    mainGameMechsRef->setScore(playerSize - 1);
                else
                    mainGameMechsRef->setScore(0);

                collide = true;
                break;
            }
        }
        
        if (!collide)
        {
            playerPosList->insertHead(objPos(x, y, '*'));
            playerPosList->removeTail();
        }

        if (checkSelfCollision())
        {
            mainGameMechsRef->setExitTrue();
            mainGameMechsRef->setLoseFlag();
        }
    }
}

enum dir {UP, DOWN, LEFT, RIGHT, STOP};