#include "Tile.h"

ShootingResult Tile::TakeShot()
{
    WasShot = true;

    if (Type == TileType::Warship)
        return ShootingResult::ShipShot;

    return ShootingResult::Miss;
}