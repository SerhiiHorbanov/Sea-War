#pragma once
#include <string>
#include <tuple>
#include <vector>

enum class MapShootingResult
{
    Miss,
    ShipShot
};

struct SeaMap
{
    enum class TileType
    {
        Sea,
        Warship,
    };

    struct Tile
    {
        TileType Type;
        bool WasShot;

        Tile(TileType type = TileType::Sea) :
            Type(type),
            WasShot(false)
        {}
        char GetChar(const bool useFogOfWar) const;
    };

    std::vector<Tile> tiles;
    std::pair<int, int> size;
    bool AnyShipsLeft;

    SeaMap() :
        AnyShipsLeft(false)
    {}

    SeaMap(const std::vector<Tile>& tiles, const std::pair<int, int>& size, bool anyShipsLeft) : 
        tiles(tiles), 
        size(size), 
        AnyShipsLeft(anyShipsLeft)
    {}

    void UpdateAnyShipsLeft();
    bool ContainsAnyAliveShips();

    int GetPositionIndex(const std::pair<int, int> position) const;
    bool IsInBounds(const std::pair<int, int> position) const;

    Tile& GetTile(const std::pair<int, int> position);
    char GetTileChar(const std::pair<int, int> position, const bool fogOfWar) const;
    std::string GetMapRowText(const int y, const bool fogOfWar) const;

    MapShootingResult ShootAtTile(const std::pair<int, int> position);

    static SeaMap GenerateRandomSeaMap(const std::pair<int, int> size);
};

const std::pair<int, int> mapSize = std::pair<int, int>(10, 10);