#include "Player.h"

constexpr int DefaultRadarScansAmount = 5;
constexpr int RoundWinsRequiredForGameWin = 3;

std::shared_ptr<Player> Player::CreateNewPlayer(const bool isBot)
{
    std::shared_ptr<SeaMap> map = SeaMap::GenerateRandomSeaMap(mapSize);

    return std::shared_ptr<Player>(new Player(0, DefaultRadarScansAmount, map, isBot));
}

bool Player::TryConsumeRadarScan()
{
    bool result = _radarScansLeft;
    _radarScansLeft -= result;
    return result;
}

void Player::WinRound()
{
    _wins++;
}

ShootingResult Player::ShootAtPosition(const std::pair<int, int> position) const
{
    return _map->ShootAtTile(position);
}

void Player::ScanAtPosition(const std::pair<int, int> position) const
{
    _map->ScanAtPosition(position);
}

void Player::RegenerateMap()
{
    _map = SeaMap::GenerateRandomSeaMap(mapSize);
}

int Player::GetRadarsLeft() const
{
    return _radarScansLeft;
}

int Player::GetWins() const
{
    return _wins;
}

bool Player::IsBot() const
{
    return _isBot;
}

const std::shared_ptr<SeaMap> Player::GetMap() const
{
    return _map;
}

bool Player::HasLostRound() const
{
    return !_map->AnyShipsLeft;
}

bool Player::HasWonGame() const
{
    return GetWins() > RoundWinsRequiredForGameWin;
}
