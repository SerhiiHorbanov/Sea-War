#pragma once
enum class ShootingResult
{
    Miss,
    ShipShot
};

enum class TileType
{
    Sea,
    Warship,
};

struct Tile
{
    TileType Type;
    bool WasShot;

    Tile(TileType type = TileType::Sea) :
        Type(type),
        WasShot(false)
    {}

    ShootingResult TakeShot();
};
