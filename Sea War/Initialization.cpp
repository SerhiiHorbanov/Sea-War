#include "Initialization.h"
#include "SeaMap.h"

void Initialization()
{
    P1Map = SeaMap::GenerateRandomSeaMap(mapSize);
    P2Map = SeaMap::GenerateRandomSeaMap(mapSize);
}