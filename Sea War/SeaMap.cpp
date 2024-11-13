#include "SeaMap.h"
#include <random>

bool IsInBounds(const std::pair<int, int> position, const std::vector<TileType>& seaMap, const int width)
{
    const int yOffset = position.second * width;
    const int xOffset = position.first;
    return seaMap.size() >= yOffset + xOffset;
}

TileType GetTile(const std::pair<int, int> position, const std::vector<TileType>& seaMap, const int width)
{
    const int yOffset = position.second * width;
    const int xOffset = position.first;
    return seaMap[yOffset + xOffset];
}

char GetTileChar(const std::pair<int, int> position, const std::vector<TileType>& seaMap, const int width)
{
    return (char)GetTile(position, seaMap, width);
}

void SetTile(const std::pair<int, int> position, std::vector<TileType>& seaMap, const int width, TileType newTile)
{
    const int yOffset = position.second * width;
    const int xOffset = position.first;
    seaMap[yOffset + xOffset] = newTile;
}

void ShootAtTile(const std::pair<int, int> position, std::vector<TileType>& seaMap, const int width)
{
    if (GetTile(position, seaMap, width) == TileType::Warship)
        SetTile(position, seaMap, width, TileType::DestroyedWarship);
}

// for now just places 10 warships randomly
std::vector<TileType> GenerateRandomSeaMap(const std::pair<int, int> size)
{
    std::vector<TileType> seaMap = std::vector<TileType>(size.first * size.second);
    
    for (int i = 0; i < 10; i++)
    {
        int x = std::rand() % size.first;
        int y = std::rand() % size.second;

        SetTile(std::pair<int, int>(x, y), seaMap, size.first, TileType::Warship);
    }

    return std::vector<TileType>();
}
