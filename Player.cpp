#include "Player.h"

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos = objPos(15, 7, '*');

    // more actions to be included
}


Player::~Player()
{
}

objPos Player::getPlayerPos() const
{
    return playerPos.getObjPos();
    // return the reference to the playerPos array list (getHeadElement)
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput();

    // Allows 90° turns, but not 180°
    if (input)
    {
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
}

void Player::movePlayer()
{
    // Shortcuts
    int xMax = mainGameMechsRef -> getBoardSizeX();
    int yMax = mainGameMechsRef -> getBoardSizeY();
    int playerX = playerPos.pos -> x;
    int playerY = playerPos.pos -> y;
    
    // Movement implements wrap-around logic
    switch(myDir)
    {
        case UP:
            playerPos.pos -> y = (playerY > 1) ? (playerY - 1) : (yMax - 2);
            break;
        case DOWN:
            playerPos.pos -> y = (playerY < (yMax - 2)) ? (playerY + 1) : 1;
            break;
        case LEFT:
            playerPos.pos -> x = (playerX > 1) ? (playerX - 1) : (xMax - 2);
            break;
        case RIGHT:
            playerPos.pos -> x = (playerX < (xMax - 2)) ? (playerX + 1) : 1;
            break;
        default:
            break;
    }
}

enum dir {UP, DOWN, LEFT, RIGHT, STOP};