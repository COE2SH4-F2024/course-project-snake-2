#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos = objPos(9, 4, '*');

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

    if (input)
    {
        switch(input)
        {
            case 'w':
                if (myDir != DOWN)
                {
                    myDir = UP;
                    cout << "UP";
                }
                break;
            case 's':
                if (myDir != UP)
                {
                    myDir = DOWN;
                    cout << "DOWN";
                }
                break;
            case 'd':
                if (myDir != LEFT)
                {
                    myDir = RIGHT;
                    cout << "RIGHT";
                }
                break;
            case 'a':
                if (myDir != RIGHT)
                {
                    myDir = LEFT;
                    cout << "LEFT";
                }
                break;
            default:
                break;
        }
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

enum dir {UP, DOWN, LEFT, RIGHT, STOP};