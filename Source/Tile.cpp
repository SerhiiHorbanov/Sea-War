#include "Tile.h"
#include <tuple>

const std::pair<char, char> tileTextures[] =
{
    {'~', '~'},// TileType::Sea
    {'W', 'x'},// TileType::Warship
};
const char fogOfWarChar = '#';

char Tile::GetChar(const bool fogOfWar) const
{
    if (fogOfWar && !WasShot)
        return fogOfWarChar;

    const std::pair<char, char> currentTilePossibleTextures = tileTextures[(int)Type];

    return WasShot ? currentTilePossibleTextures.second : currentTilePossibleTextures.first;
}

MapShootingResult Tile::TakeShot()
{
    WasShot = true;

    if (Type == TileType::Warship)
        return MapShootingResult::ShipShot;

    return MapShootingResult::Miss;
}