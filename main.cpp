#include <memory>
#include "Source/SeaWar.h"

int main()
{
    std::unique_ptr<SeaWar> game = std::unique_ptr<SeaWar>(new SeaWar());
    game->Run();

    return 0;
}