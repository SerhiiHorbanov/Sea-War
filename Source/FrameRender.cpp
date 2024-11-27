#include "FrameRender.h"
#include <iostream>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string AskingPlayerForActionText = "enter action (r/s) and coordinates (x,y):\n";

const std::pair<char, char> tileTextures[] =
{
    {'~', '~'},// TileType::Sea
    {'W', 'x'},// TileType::Warship
};
const char fogOfWarChar = '#';

void FrameRender::ReserveMemory()
{
    const int lengthReserving = EvaluateImageLength();
    text.reserve(lengthReserving);
}

int FrameRender::EvaluateImageLength() const
{
    int result = 0;

    result += CurrentPlayerMapText.length();
    result += CurrentEnemyMapText.length();
    result++;// newline
    result += GapBetweenMaps.length() * mapSize.second;// all the gaps between map rows
    result += mapSize.first * 2 * mapSize.second;// both map widths and newlines for each map row
    result += mapSize.second;// newlines between rows of maps
    result++;// newline
    result += AskingPlayerForActionText.length();

    return result;
}

FrameRender FrameRender::Render(const Player& attackingPlayer, const Player& attackedPlayer)
{
    FrameRender result = FrameRender();

    result.ReserveMemory();
    result.AddPlayerTextsLine();
    result.AddPlayersMapsLines(attackingPlayer, attackedPlayer);
    result.AddAskingPlayerForActionLine();

    return result;
}

void FrameRender::Display() const
{
    std::system("cls");
    std::cout << text;
}

char GetTileChar(const Tile& tile, const bool fogOfWar)
{
    if (fogOfWar && !tile.WasShot)
        return fogOfWarChar;

    const std::pair<char, char> currentTilePossibleTextures = tileTextures[(int)tile.Type];

    return tile.WasShot ? currentTilePossibleTextures.second : currentTilePossibleTextures.first;
}

char GetTileChar(const SeaMap& seaMap, const std::pair<int, int> position, const bool fogOfWar)
{
    if (!seaMap.scannedWithRadar)
        return GetTileChar(seaMap.GetTileConst(position), fogOfWar);
    else if (!fogOfWar)
        return GetTileChar(seaMap.GetTileConst(position), false);

    return GetTileChar(seaMap.GetTileConst(position), !seaMap.IsScanned(position));
}

std::string GetMapRowAsText(const SeaMap& seaMap, const int y, const bool fogOfWar)
{
    const int width = seaMap.size.first;

    std::string result;
    result.reserve(width);

    for (int x = 0; x < width; x++)
    {
        std::pair<int, int> position = std::pair<int, int>(x, y);
        
        result += GetTileChar(seaMap, position, fogOfWar);
    }

    return result;
}

void FrameRender::AddPlayerTextsLine()
{
    text += CurrentPlayerMapText;
    const int GapBetweenPlayerTextsLength = mapSize.first + GapBetweenMaps.length() - CurrentPlayerMapText.length();
    text += std::string(GapBetweenPlayerTextsLength, ' ');
    text += CurrentEnemyMapText;
    text += '\n';
}

void FrameRender::AddPlayersMapsLines(const Player& attackingPlayer, const Player& attackedPlayer)
{
    const SeaMap& attackingPlayerMap = attackingPlayer.GetMap();
    const SeaMap& attackedPlayerMap = attackedPlayer.GetMap();

    for (int y = 0; y < mapSize.second; y++)
    {
        text += GetMapRowAsText(attackingPlayerMap, y, false);
        text += GapBetweenMaps;
        text += GetMapRowAsText(attackedPlayerMap, y, true);
        text += '\n';
    }
}

void FrameRender::AddAskingPlayerForActionLine()
{
    text += AskingPlayerForActionText;
}