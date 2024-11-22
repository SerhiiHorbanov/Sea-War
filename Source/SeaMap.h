#pragma once
#include <string>
#include <tuple>
#include <vector>

enum class MapShootingResult
{
    Miss,
    ShipDestroyed
};

struct SeaMap
{
    enum class TileType : char
    {
        Sea = '~',
        Warship = 'W',
        DestroyedWarship = 'x',
    };

    std::vector<TileType> tiles;
    std::pair<int, int> size;
    bool AnyShipsLeft;

    SeaMap() :
        AnyShipsLeft(false)
    {}

    SeaMap(const std::vector<TileType>& tiles, const std::pair<int, int>& size, bool anyShipsLeft) : 
        tiles(tiles), 
        size(size), 
        AnyShipsLeft(anyShipsLeft)
    {}

    void UpdateAnyShipsLeft();
    bool ContainsAnyAliveShips();

    int GetPositionIndex(const std::pair<int, int> position) const;
    bool IsInBounds(const std::pair<int, int> position) const;

    TileType GetTile(const std::pair<int, int> position) const;
    char GetTileChar(const std::pair<int, int> position) const;
    std::string GetMapRowText(const int y) const;

    void SetTile(const std::pair<int, int> position, TileType newTile);
    MapShootingResult ShootAtTile(const std::pair<int, int> position);

    static SeaMap GenerateRandomSeaMap(const std::pair<int, int> size);
};

const std::pair<int, int> mapSize = std::pair<int, int>(10, 10);