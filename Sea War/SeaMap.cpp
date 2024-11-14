#include "SeaMap.h"
#include <random>

SeaMap P1Map;
SeaMap P2Map;

int SeaMap::GetPositionIndex(const std::pair<int, int> position) const
{
    const int yOffset = position.second * size.first;
    const int xOffset = position.first;
    return yOffset + xOffset;
}
bool SeaMap::IsInBounds(const std::pair<int, int> position) const
{
    bool isXInBounds = position.first >= 0 && position.first < size.first;
    bool isYInBounds = position.second >= 0 && position.second < size.second;
    return isXInBounds && isYInBounds;
}
SeaMap::TileType SeaMap::GetTile(const std::pair<int, int> position) const
{
    const int index = GetPositionIndex(position);
    return tiles[index];
}
char SeaMap::GetTileChar(const std::pair<int, int> position) const
{
    return (char)GetTile(position);
}
void SeaMap::SetTile(const std::pair<int, int> position, TileType newTile)
{
    const int index = GetPositionIndex(position);
    tiles[index] = newTile;
}
void SeaMap::ShootAtTile(const std::pair<int, int> position)
{
    if (GetTile(position) == TileType::Warship)
        SetTile(position, TileType::DestroyedWarship);
}

// for now just tries to place a warship 10 times
SeaMap SeaMap::GenerateRandomSeaMap(const std::pair<int, int> size)
{
    const int tilesAmount = size.first * size.second;
    std::vector<TileType> tiles = std::vector<TileType>(tilesAmount);

    for (int i = 0; i < tilesAmount; i++)
        tiles[i] = TileType::Sea;

    for (int i = 0; i < 10; i++)
    {
        int index = std::rand() % tilesAmount;

        tiles[index] = TileType::Warship;
    }

    return SeaMap(tiles, size);
}

/*namespace
{
    SeaMap P1SeaMap = SeaMap();
    SeaMap P2SeaMap = SeaMap();
}*/
