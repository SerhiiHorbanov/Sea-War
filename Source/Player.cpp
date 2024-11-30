#include "Player.h"

std::shared_ptr<Player> Player::CreateNewPlayer()
{
    std::shared_ptr<SeaMap> map = SeaMap::GenerateRandomSeaMap(mapSize);

    return std::shared_ptr<Player>(new Player(map, 5, false));
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

void Player::TryScanAtPosition(const std::pair<int, int> position)
{
    if (TryConsumeRadarScan())
        _map->ScanAtPosition(position);
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
