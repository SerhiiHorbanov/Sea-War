#include "FrameRender.h"
#include <iostream>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string AskingPlayerWhereToShootText = "Where would you like to shoot?";

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
    result += AskingPlayerWhereToShootText.length();

    return result;
}

FrameRender FrameRender::Render(const SeaMap& AttackingPlayer, const SeaMap& AttackedPlayer)
{
    FrameRender result = FrameRender();

    result.ReserveMemory();
    result.AddPlayerTextsLine();
    result.AddPlayersMapsLines(AttackingPlayer, AttackedPlayer);

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

std::string GetMapRowAsText(const SeaMap& playerMap, const int y, const bool fogOfWar)
{
    std::string result;
    result.reserve(playerMap.size.first);

    for (int x = 0; x < playerMap.size.first; x++)
    {
        std::pair<int, int> position = std::pair<int, int>(x, y);
        result += GetTileChar(playerMap.GetTileConst(position), fogOfWar);
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

void FrameRender::AddPlayersMapsLines(const SeaMap& AttackingPlayer, const SeaMap& AttackedPlayer)
{
    for (int y = 0; y < mapSize.second; y++)
    {
        text += GetMapRowAsText(AttackingPlayer, y, false);
        text += GapBetweenMaps;
        text += GetMapRowAsText(AttackedPlayer, y, true);
        text += '\n';
    }
}