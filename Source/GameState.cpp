#include "GameState.h"

void GameState::RunFrame(Game* handler)
{
    Render();
    Input();
    Update(handler);
}
