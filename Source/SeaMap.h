#pragma once
#include <memory>
#include <vector>
#include "Tile.h"

struct SeaMap
{
    std::vector<Tile> tiles;
    std::pair<int, int> size;
    bool AnyShipsLeft;

    std::pair<int, int> scannedAtPosition;
    bool scannedWithRadar;

    SeaMap() :
        size(),
        AnyShipsLeft(),
        scannedAtPosition(),
        scannedWithRadar()
    {}

    SeaMap(const std::vector<Tile>& tiles, const std::pair<int, int>& size, bool AnyShipsLeft, const std::pair<int, int>& scannedAtPosition, bool scannedWithRadar) :
        tiles(tiles),
        size(size),
        AnyShipsLeft(AnyShipsLeft),
        scannedAtPosition(scannedAtPosition),
        scannedWithRadar(scannedWithRadar)
    {}

    void UpdateAnyShipsLeft();
    bool ContainsAnyAliveShips() const;

    int GetPositionIndex(const std::pair<int, int> position) const;
    bool IsInBounds(const std::pair<int, int> position) const;

    Tile& GetTile(const std::pair<int, int> position);
    const Tile& GetTileConst(const std::pair<int, int> position) const;

    ShootingResult ShootAtTile(const std::pair<int, int> position);

    void ScanAtPosition(const std::pair<int, int> position);
    int GetDistanceSquaredToScannedPosition(const std::pair<int, int> position) const;
    bool IsScanned(const std::pair<int, int> position) const;
    bool HasFogOfWarAtPosition(const std::pair<int, int> position) const;

    std::pair<int, int> GetRandomNotShotTile() const;

    static std::shared_ptr<SeaMap> GenerateRandomSeaMap(const std::pair<int, int> size);
};
const std::pair<int, int> mapSize = std::pair<int, int>(10, 10);