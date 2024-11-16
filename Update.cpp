#include "Update.h"
#include "Input.h"
#include "SeaMap.h"

void Update()
{
    TryShooting();
}

void TryShooting()
{
    if (isValidShootingPosition)
    {
        AttackedPlayer->ShootAtTile(shootingPosition);
        std::swap(AttackingPlayer, AttackedPlayer);
    }
}

bool GameContinues()
{
    const bool firstPlayerAlive = P1Map.ContainsAnyAliveShips();
    const bool secondPlayerAlive = P2Map.ContainsAnyAliveShips();
    return firstPlayerAlive && secondPlayerAlive;
}