#pragma once
#include <memory>
#include "SeaMap.h"

class Player
{
private:
    int _wins;
    int _radarScansLeft;
    std::shared_ptr<SeaMap> _map;
    bool _isBot;

    Player(const int wins, const int radarScansLeft, std::shared_ptr<SeaMap> map, const bool isBot) :
        _wins(wins),
        _radarScansLeft(radarScansLeft),
        _map(map),
        _isBot(isBot)
    {}

public:
    static std::shared_ptr<Player> CreateNewPlayer(const bool isBot);

    bool TryConsumeRadarScan();
    void WinRound();
    
    ShootingResult ShootAtPosition(const std::pair<int, int> position) const;
    void ScanAtPosition(const std::pair<int, int> position) const;

    void RegenerateMap();
    const std::shared_ptr<SeaMap> GetMap() const;

    int GetRadarsLeft() const;
    int GetWins() const;
    bool IsBot() const;
    bool HasLostRound() const;
    bool HasWonGame() const;
};

