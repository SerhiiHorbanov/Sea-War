#include "Initialization.h"
#include <random>
#include "SeaMap.h"

void Initialization()
{
    SetRandomSeed();
    SetRandomSeaMaps();
    SetAttackingAndAttackedMaps();
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

void SetAttackingAndAttackedMaps()
{
    AttackingPlayer = &P1Map;
    AttackedPlayer = &P2Map;
}