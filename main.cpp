#include <iostream>
#include "Initialization.h"
#include "Input.h"
#include "Render.h"
#include "Update.h"

int main()
{
    Initialization();

    while (GameContinues())
    {
        Render();
        Input();
        Update();
    }

    return 0;
}