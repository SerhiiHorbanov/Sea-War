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