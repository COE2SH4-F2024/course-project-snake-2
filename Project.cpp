#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
using namespace std;

#define DELAY_CONST 100000
#define row 10
#define size 20

objPos board;
GameMechs* gamemechs = nullptr;
Player* player = nullptr;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{
    Initialize();

    while(!gamemechs -> getExitFlagStatus())  
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

    board = objPos();

    gamemechs = new GameMechs();
    player = new Player(gamemechs);
}

void GetInput(void)
{
    char input = MacUILib_getChar();
    gamemechs -> setInput(input);
}

void RunLogic(void)
{
    char input = gamemechs -> getInput();

    if(input != 0)
    {
        switch(input)
        {
            case 27:
                gamemechs -> setExitTrue();
                break;
            case 'x':
                gamemechs -> incrementScore();
                break;
            case 'z':
                gamemechs -> setLoseFlag();
                gamemechs -> setExitTrue();
                break;
            default:
                player->updatePlayerDir();
                break;
        }
    }
    
    gamemechs -> clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i == 0) || (i == 9))
                board.setObjPos(j, i, '#');
            else if ((j == 0) || (j == 19))
                board.setObjPos(j, i, '#');
            else if ((i == player->getPlayerPos().pos->y) && (j == player->getPlayerPos().pos->x))
                board.setObjPos(j, i, player->getPlayerPos().symbol);
            else
                board.setObjPos(j, i, ' ');

            if (j != 19)
                MacUILib_printf("%c", board.getSymbol());
            else
                MacUILib_printf("%c\n", board.getSymbol());
        }
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

    MacUILib_uninit();
}
