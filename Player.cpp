#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
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
        playerPosList->insertHead(objPos(x, y, '*'));
        playerPosList->removeTail();
    }
}

enum dir {UP, DOWN, LEFT, RIGHT, STOP};