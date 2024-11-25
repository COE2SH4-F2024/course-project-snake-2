#include "Player.h"

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
    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

enum dir {UP, DOWN, LEFT, RIGHT, STOP};