#include "Initialization.h"
#include "SeaMap.h"

void Initialization()
{
    P1SeaMap = GenerateRandomSeaMap(mapSize);
    P2SeaMap = GenerateRandomSeaMap(mapSize);
}