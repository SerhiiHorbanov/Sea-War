#include <memory>
#include "Source/Game.h"

int main()
{
    std::unique_ptr<Game> game = std::unique_ptr<Game>(new Game());
    game->Run();

    return 0;
}