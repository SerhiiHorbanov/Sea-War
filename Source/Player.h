#pragma once
#include <memory>
#include "SeaMap.h"

class Player
{
private:
    int _radarScansLeft;
    std::shared_ptr<SeaMap> _map;
    bool _isBot;

    Player(std::shared_ptr<SeaMap> map, const int radarScansLeft, const bool isBot) :
        _map(map),
        _radarScansLeft(radarScansLeft),
        _isBot(isBot)
    {}

public:
    bool TryConsumeRadarScan();
    static std::shared_ptr<Player> CreateNewPlayer(const bool isBot);

    ShootingResult ShootAtPosition(const std::pair<int, int> position);
    void ScanAtPosition(const std::pair<int, int> position);

    const SeaMap& GetMap() const;

    int GetRadarsLeft() const;
    bool IsBot() const;
    bool HasLost() const;
};

