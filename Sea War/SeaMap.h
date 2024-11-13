#pragma once
#include <tuple>
#include <vector>

enum class TileType : char
{
    Sea,
    Warship,
    DestroyedWarship,
};

const std::pair<int, int> mapSize = std::pair<int, int>(10, 10);

std::vector<TileType> P1SeaMap;
std::vector<TileType> P2SeaMap;

bool IsInBounds(const std::pair<int, int> position, const std::vector<TileType>& seaMap, const int width);

TileType GetTile(const std::pair<int, int> position, const std::vector<TileType>& seaMap, const int width);
char GetTileChar(const std::pair<int, int> position, const std::vector<TileType>& seaMap, const int width);

void SetTile(const std::pair<int, int> position, std::vector<TileType>& seaMap, const int width, TileType newTile);
void ShootAtTile(const std::pair<int, int> position, std::vector<TileType>& seaMap, const int width);

std::vector<TileType> GenerateRandomSeaMap(const std::pair<int, int> size);
