#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
using namespace std;

#define DELAY_CONST 100000

objPos board;
GameMechs* gamemechs = nullptr;
Player* player = nullptr;
char input;

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
    
    input = 0;
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
        gamemechs -> setInput(input);
    }
}

void RunLogic(void)
{
    input = gamemechs -> getInput();

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
                player -> updatePlayerDir();
                break;
        }
    }
    
    gamemechs -> clearInput();

    player -> movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int columns = gamemechs -> getBoardSizeY();
    int rows = gamemechs -> getBoardSizeX();
    int playerX = player -> getPlayerPos().pos->x;
    int playerY = player -> getPlayerPos().pos->y;
    int playerSym = player -> getPlayerPos().symbol;

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if ((i == 0) || (i == (columns - 1)))
                board.setObjPos(j, i, '#');
            else if ((j == 0) || (j == (rows - 1)))
                board.setObjPos(j, i, '#');
            else if ((i == playerY) && (j == playerX))
                board.setObjPos(j, i, playerSym);
            else
                board.setObjPos(j, i, ' ');

            if (j != (rows - 1))
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
