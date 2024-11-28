#include "GameMechs.h"

GameMechs::GameMechs()
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

GameMechs::~GameMechs()
{
    // No heap allocations, therefore no destructor needed
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    
char GameMechs::getInput() const
{
    return input;
}

void GameMechs::setScore(int newScore)
{
    score = newScore;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::decrementScore()
{
    score--;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}