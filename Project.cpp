#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000
#define row 10
#define size 20

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{
    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos a = objPos();
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if ((i == 0) || (i == 9))
                a.setObjPos(j, i, '#');
            else if ((j == 0) || (j == 19))
                a.setObjPos(j, i, '#');
            else
                a.setObjPos(j, i, ' ');

            if (j != 19)
                MacUILib_printf("%c", a.getSymbol());
            else
                MacUILib_printf("%c\n", a.getSymbol());
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

    MacUILib_uninit();
}
