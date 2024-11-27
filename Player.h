#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{    
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here

    private:
        objPosArrayList* playerPosList;
        enum Dir myDir;

        // Reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

        // Reference to the Main Food Class
        Food* mainFoodRef;
};

#endif