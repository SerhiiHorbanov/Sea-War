#pragma once
#include <memory>
#include "SeaMap.h"

class Player
{
private:
    int _radarScansLeft;
    std::unique_ptr<SeaMap> _map;

private:
    Player(std::unique_ptr<SeaMap>& map, const int radarScansLeft) :
        _map(map.release()), 
        _radarScansLeft(radarScansLeft)
    {}

    bool TryConsumeRadarScan();

public:
    static std::shared_ptr<Player> CreateNewPlayer();

    ShootingResult ShootAtPosition(const std::pair<int, int> position);
    void TryScanAtPosition(const std::pair<int, int> position);

    const SeaMap& GetMap() const;
    const Tile& GetMapTile(const std::pair<int, int> position) const;

    bool HasLost();
};

