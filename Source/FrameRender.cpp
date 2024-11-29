#include "FrameRender.h"
#include <iostream>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string AskingPlayerForActionText = "enter action (r/s) and coordinates (x,y):\n";

const ConsoleTextAttribute PlayerTextsAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute MapTextAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute PointedAtTileAttribute = ConsoleTextAttribute(ConsoleColor::Black, ConsoleColor::Red);//, false, false, false, false, true);
const ConsoleTextAttribute AskingPlayerForActionAttribute = ConsoleTextAttribute(ConsoleColor::LightGreen);

const std::pair<char, char> tileTextures[] =
{
    {'~', '~'},// TileType::Sea
    {'W', 'x'},// TileType::Warship
};
const char fogOfWarChar = '#';

void FrameRender::ReserveMemory()
{
    const int lengthReserving = EvaluateImageLength();
    //text.reserve(lengthReserving);
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

FrameRender FrameRender::Render(const Player& attackingPlayer, const Player& attackedPlayer, const std::pair<int, int> actionPosition)
{
    FrameRender result = FrameRender();

    result.ReserveMemory();
    result.AddPlayerTextsLine();
    result.AddPlayersMapsLines(attackingPlayer, attackedPlayer, actionPosition);
    result.AddAskingPlayerForActionLine();

    return result;
}

void FrameRender::Display() const
{
    std::system("cls");
    text.Print();
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
    const Tile& tile = seaMap.GetTileConst(position);

    if (!seaMap.scannedWithRadar)
        return GetTileChar(tile, fogOfWar);
    else if (!fogOfWar)
        return GetTileChar(tile, false);

    return GetTileChar(tile, !seaMap.IsScanned(position));
}

void FrameRender::AddMapRow(const SeaMap& seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar)
{
    const int width = seaMap.size.first;

    for (int x = 0; x < width; x++)
    {
        std::pair<int, int> position = std::pair<int, int>(x, y);

        ConsoleTextAttribute attribute = MapTextAttribute;
        if (actionPosition == position && fogOfWar)
            attribute = PointedAtTileAttribute;

        text.Append(attribute, GetTileChar(seaMap, position, fogOfWar));
    }
}

void FrameRender::AddPlayerTextsLine()
{
    text.Append(PlayerTextsAttribute, CurrentPlayerMapText);

    const int GapBetweenPlayerTextsLength = mapSize.first + GapBetweenMaps.length() - CurrentPlayerMapText.length();
    text.Append(PlayerTextsAttribute, std::string(GapBetweenPlayerTextsLength, ' '));

    text.Append(PlayerTextsAttribute, CurrentEnemyMapText);
    text.Append(PlayerTextsAttribute, '\n');
}

void FrameRender::AddPlayersMapsLines(const Player& attackingPlayer, const Player& attackedPlayer, const std::pair<int, int> actionPosition)
{
    const SeaMap& attackingPlayerMap = attackingPlayer.GetMap();
    const SeaMap& attackedPlayerMap = attackedPlayer.GetMap();

    for (int y = 0; y < mapSize.second; y++)
    {
        AddMapRow(attackingPlayerMap, actionPosition, y, false);
        text.Append(MapTextAttribute, GapBetweenMaps);
        AddMapRow(attackedPlayerMap, actionPosition, y, true);
        text.Append(MapTextAttribute, '\n');
    }
}

void FrameRender::AddAskingPlayerForActionLine()
{
    text.Append(AskingPlayerForActionAttribute, AskingPlayerForActionText);
}