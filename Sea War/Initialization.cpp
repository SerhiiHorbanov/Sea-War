#include "Initialization.h"
#include <random>
#include "SeaMap.h"

void Initialization()
{
    SetRandomSeed();
    SetRandomSeaMaps();
}

void SetRandomSeed()
{
    std::srand(time(NULL));
}

void SetRandomSeaMaps()
{
    P1Map = SeaMap::GenerateRandomSeaMap(mapSize);
    P2Map = SeaMap::GenerateRandomSeaMap(mapSize);
}
