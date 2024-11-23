#include "SeaMap.h"
#include <random>

const std::pair<char, char> tileTextures[] =
{
    {'~', '~'},// TileType::Sea
    {'W', 'x'},// TileType::Warship
};
const char fogOfWarChar = '#';

void SeaMap::UpdateAnyShipsLeft()
{
    AnyShipsLeft = ContainsAnyAliveShips();
}

bool SeaMap::ContainsAnyAliveShips()
{
    const int tilesAmount = tiles.size();

    for (int i = 0; i < tilesAmount; i++)
    {
        if (tiles[i].Type == TileType::Warship)
            return true;
    }
    return false;
}

int SeaMap::GetPositionIndex(const std::pair<int, int> position) const
{
    const int yOffset = position.second * size.first;
    const int xOffset = position.first;
    return yOffset + xOffset;
}

bool SeaMap::IsInBounds(const std::pair<int, int> position) const
{
    const bool isXInBounds = position.first >= 0 && position.first < size.first;
    const bool isYInBounds = position.second >= 0 && position.second < size.second;
    return isXInBounds && isYInBounds;
}

SeaMap::Tile& SeaMap::GetTile(const std::pair<int, int> position)
{
    const int index = GetPositionIndex(position);

    return tiles[index];
}

char SeaMap::GetTileChar(const std::pair<int, int> position, const bool fogOfWar) const
{
    const int index = GetPositionIndex(position);
    const Tile tile = tiles[index];

    return tile.GetChar(fogOfWar);
}

std::string SeaMap::GetMapRowText(const int y, const bool fogOfWar) const
{
    std::string result;
    result.reserve(size.first);

    for (int x = 0; x < size.first; x++)
    {
        const std::pair<int, int> position = std::pair<int, int>(x, y);

        result += GetTileChar(position, fogOfWar);
    }

    return result;
}

MapShootingResult SeaMap::ShootAtTile(const std::pair<int, int> position)
{
    Tile& tile = GetTile(position);
    tile.WasShot = true;
    
    if (tile.Type == TileType::Warship)
    {
        UpdateAnyShipsLeft();
        return MapShootingResult::ShipShot;
    }

    return MapShootingResult::Miss;
}

// for now just tries to place a warship 10 times
SeaMap SeaMap::GenerateRandomSeaMap(const std::pair<int, int> size)
{
    const int tilesAmount = size.first * size.second;
    std::vector<Tile> tiles = std::vector<Tile>(tilesAmount);

    for (int i = 0; i < tilesAmount; i++)
        tiles[i] = TileType::Sea;

    for (int i = 0; i < 10; i++)
    {
        const int index = std::rand() % tilesAmount;

        tiles[index] = Tile(TileType::Warship);
    }

    return SeaMap(tiles, size, true);
}

char SeaMap::Tile::GetChar(const bool fogOfWar) const
{
    if (fogOfWar && !WasShot)
        return fogOfWarChar;

    const std::pair<char, char> currentTilePossibleTextures = tileTextures[(int)Type];

    return WasShot ? currentTilePossibleTextures.second : currentTilePossibleTextures.first;
}