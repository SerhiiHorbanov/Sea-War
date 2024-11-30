#include "Player.h"

std::shared_ptr<Player> Player::CreateNewPlayer(const bool isBot)
{
    std::shared_ptr<SeaMap> map = SeaMap::GenerateRandomSeaMap(mapSize);

    return std::shared_ptr<Player>(new Player(map, 5, isBot));
}

bool Player::TryConsumeRadarScan()
{
    bool result = _radarScansLeft;
    _radarScansLeft -= result;
    return result;
}

ShootingResult Player::ShootAtPosition(const std::pair<int, int> position)
{
    return _map->ShootAtTile(position);
}

void Player::ScanAtPosition(const std::pair<int, int> position)
{
    _map->ScanAtPosition(position);
}

int Player::GetRadarsLeft() const
{
    return _radarScansLeft;
}

bool Player::IsBot() const
{
    return _isBot;
}

const SeaMap& Player::GetMap() const
{
    return *_map;
}

const Tile& Player::GetMapTile(const std::pair<int, int> position) const
{
    return _map->GetTileConst(position);
}

bool Player::HasLost()
{
    return !_map->AnyShipsLeft;
}
