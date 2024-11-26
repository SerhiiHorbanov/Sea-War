#include "Tile.h"

MapShootingResult Tile::TakeShot()
{
    WasShot = true;

    if (Type == TileType::Warship)
        return MapShootingResult::ShipShot;

    return MapShootingResult::Miss;
}