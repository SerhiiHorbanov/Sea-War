#include "SeaMap.h"
#include <random>
const int ScanningRadius = 10;

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

Tile& SeaMap::GetTile(const std::pair<int, int> position)
{
    const int index = GetPositionIndex(position);

    return tiles[index];
}

const Tile& SeaMap::GetTileConst(const std::pair<int, int> position) const
{
    const int index = GetPositionIndex(position);

    return tiles[index];
}

ShootingResult SeaMap::ShootAtTile(const std::pair<int, int> position)
{
    scannedWithRadar = false;

    Tile& tile = GetTile(position);

    ShootingResult shootingResult = tile.TakeShot();

    if (shootingResult == ShootingResult::ShipShot)
        UpdateAnyShipsLeft();

    return shootingResult;
}

void SeaMap::ScanAtPosition(const std::pair<int, int> position)
{
    scannedAtPosition = position;
    scannedWithRadar = true;
}

int SeaMap::GetDistanceSquaredToScannedPosition(const std::pair<int, int> position) const
{
    int x = std::abs(position.first - scannedAtPosition.first);
    int y = std::abs(position.second - scannedAtPosition.second);

    return (x * x) + (y * y);
}

bool SeaMap::IsScanned(const std::pair<int, int> position) const
{
    return GetDistanceSquaredToScannedPosition(position) < ScanningRadius;
}

// for now just tries to place a warship 10 times
std::shared_ptr<SeaMap> SeaMap::GenerateRandomSeaMap(const std::pair<int, int> size)
{
    const int tilesAmount = size.first * size.second;
    std::vector<Tile> tiles = std::vector<Tile>(tilesAmount);

    for (int i = 0; i < 10; i++)
    {
        const int index = std::rand() % tilesAmount;

        tiles[index] = Tile(TileType::Warship);
    }

    SeaMap* seaMap = new SeaMap(tiles, size, true, std::pair<int, int>(), false);

    return std::shared_ptr<SeaMap>(seaMap);
}