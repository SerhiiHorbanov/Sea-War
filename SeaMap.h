#pragma once
#include <tuple>
#include <vector>

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


    SeaMap() :
        tiles(),
        size()
    {}
    SeaMap(const std::vector<TileType>& tiles, const std::pair<int, int>& size) : 
        tiles(tiles), 
        size(size)
    {}

    bool ContainsAnyAliveShips() const;

    int GetPositionIndex(const std::pair<int, int> position) const;
    bool IsInBounds(const std::pair<int, int> position) const;

    TileType GetTile(const std::pair<int, int> position) const;
    char GetTileChar(const std::pair<int, int> position) const;

    void SetTile(const std::pair<int, int> position, TileType newTile);
    void ShootAtTile(const std::pair<int, int> position);

    static SeaMap GenerateRandomSeaMap(const std::pair<int, int> size);
};

extern SeaMap P1Map;
extern SeaMap P2Map;
extern SeaMap* AttackingPlayer;
extern SeaMap* AttackedPlayer;

const std::pair<int, int> mapSize = std::pair<int, int>(10, 10);
