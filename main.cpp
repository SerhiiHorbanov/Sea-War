#include <iostream>
#include "Source/SeaWar.h"

int main()
{
    SeaWar game = SeaWar();
    game.Initialization();

    while (game.GameContinues())
    {
        game.Render();
        game.Input();
        game.Update();
    }

    return 0;
}