#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define LOSE_DELAY_CONST 2000000

GameMechs* gamemechs = nullptr;
Player* player = nullptr;
Food* food = nullptr;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while (!gamemechs->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    srand(time(NULL));

    gamemechs = new GameMechs();
    food = new Food(gamemechs);
    player = new Player(gamemechs, food);

    food->generateFood(player->getPlayerPos());
}

void GetInput(void)
{
    if (MacUILib_hasChar()) // Allows for asynchronous logic
    {
        char input = MacUILib_getChar();
        gamemechs->setInput(input);
    }
}

void RunLogic(void)
{
    char input = gamemechs->getInput();

    if (input != 0)
    {
        switch(input)
        {
            case 27:
                gamemechs->setExitTrue();
                break;
            default: // Only attempts to update player movement if exit key is not pressed
                player->updatePlayerDir();
                break;
        }
    }

    gamemechs->clearInput();

    // Player loses if snake size is 0 or self-collision
    if (player->getPlayerPos()->getSize() <= 0)
    {
        gamemechs->setLoseFlag();
        gamemechs->setExitTrue();
    }
    else
        player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Shortcuts
    int columns = gamemechs->getBoardSizeY();
    int rows = gamemechs->getBoardSizeX();

    bool objItem = false;
    char body = '\0';
    objPosArrayList* snake = player->getPlayerPos();
    objPosArrayList* foodPos = food->getFoodPos();

    if (!gamemechs->getLoseFlagStatus())
    {
        MacUILib_printf("%d\n", gamemechs->getScore());

        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                objItem = false;

                for (int k = 0; k < snake->getSize(); k++)
                {
                    objPos snakeBody = snake->getElement(k);
                    
                    if (snakeBody.pos->x == j && snakeBody.pos->y == i)
                    {
                        objItem = true;
                        body = snakeBody.getSymbol();
                        break;
                    } 
                }

                for (int k = 0; k < foodPos->getSize(); k++)
                {
                    objPos singleFood = foodPos->getElement(k);

                    if (singleFood.pos->x == j && singleFood.pos->y == i)
                    {
                        objItem = true;
                        body = singleFood.getSymbol();
                        break;
                    }
                }

                if (i == 0 || i == (columns - 1) || j == 0 || j == (rows - 1))
                    MacUILib_printf("%c", '#');
                else if (objItem)
                    MacUILib_printf("%c", body);
                else
                    MacUILib_printf(" ");      
            }
            MacUILib_printf("\n");
        }
    }
    else
        MacUILib_printf("Game Over!\nYour Final Score was %d", gamemechs->getScore());

}

void LoopDelay(void)
{
    if (!gamemechs->getLoseFlagStatus())
        MacUILib_Delay(DELAY_CONST); // 0.1s delay
    else
        MacUILib_Delay(LOSE_DELAY_CONST); // 2s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete player;
    player = nullptr;

    delete gamemechs;
    gamemechs = nullptr;

    delete food;
    food = nullptr;

    MacUILib_uninit();
}
