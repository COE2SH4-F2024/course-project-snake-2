#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

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

    gamemechs = new GameMechs();
    player = new Player(gamemechs);
    food = new Food();
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

    // gamemechs->incrementScore();
    // gamemechs->setLoseFlag();
    // gamemechs->setExitTrue();

    gamemechs->clearInput();

    player->movePlayer();    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Shortcuts
    int columns = gamemechs->getBoardSizeY();
    int rows = gamemechs->getBoardSizeX();

    bool snakePart = false;
    char body = '\0';
    objPosArrayList* snake = player->getPlayerPos();

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            snakePart = false;

            for (int k = 0; k < snake->getSize(); k++)
            {
                objPos snakeBody = snake->getElement(k);
                
                if (snakeBody.pos->x == j && snakeBody.pos->y == i)
                {
                    snakePart = true;
                    body = snakeBody.getSymbol();
                    break;
                }
            }

            if (i == 0 || i == (columns - 1) || j == 0 || j == (rows - 1))
                MacUILib_printf("%c", '#');
            else if (snakePart)
                MacUILib_printf("%c", body);
            else
                MacUILib_printf(" ");      
        }
        MacUILib_printf("\n");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
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