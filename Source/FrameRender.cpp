#include "FrameRender.h"
#include <Windows.h>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string TipText = "press W/A/S/D to move. press E to shoot. press R to scan with radar\n";
const std::string PlayerRadarScansLeftText = "radar scans left:";

const ConsoleTextAttribute PlayerTextsAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute MapTextAttribute = ConsoleTextAttribute();
const ConsoleTextAttribute PointedAtTileAttribute = ConsoleTextAttribute(ConsoleColor::Black, ConsoleColor::Red);//, false, false, false, false, true);
const ConsoleTextAttribute TipTextAttribute = ConsoleTextAttribute(ConsoleColor::LightGreen);

constexpr int SleepMilliseconds = 1000;

constexpr std::pair<char, char> TileTextures[] =
{
    {'~', '-'},// TileType::Sea
    {'W', 'x'},// TileType::Warship
};
constexpr char FogOfWarChar = '#';

void FrameRender::ReserveMemory()
{
    const int lengthReserving = EvaluateImageLength();
    _text->Reserve(lengthReserving);
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
    result += TipText.length();
    result++;// newline
    result += PlayerRadarScansLeftText.length();
    result++;// scans left amount number length

    return result;
}

void FrameRender::Display() const
{
    std::system("cls");
    _text->Print();

    if (_areBothPlayersBots)
        Sleep(SleepMilliseconds);
}

void FrameRender::Render(const std::shared_ptr<Player> attackingPlayer, const std::shared_ptr<Player> attackedPlayer, const std::pair<int, int> actionPosition)
{
    InitializeAreBothPlayersBots(attackingPlayer, attackedPlayer);
    ReserveMemory();
    AddPlayerTextsLine();
    AddPlayersMapsLines(attackingPlayer, attackedPlayer, actionPosition);
    AddTipLine();
    AddPlayersRadarScansLeftText(attackingPlayer);
}

void FrameRender::InitializeAreBothPlayersBots(const std::shared_ptr<Player> attackingPlayer, const std::shared_ptr<Player> attackedPlayer)
{
    _areBothPlayersBots = attackedPlayer->IsBot() && attackingPlayer->IsBot();
}

char GetTileChar(const Tile& tile, const bool fogOfWar)
{
    if (fogOfWar && !tile.WasShot)
        return FogOfWarChar;

    const std::pair<char, char> currentTilePossibleTextures = TileTextures[(int)tile.Type];

    return tile.WasShot ? currentTilePossibleTextures.second : currentTilePossibleTextures.first;
}

char GetTileChar(const std::shared_ptr<SeaMap> seaMap, const std::pair<int, int> position, const bool fogOfWar)
{
    const Tile& tile = seaMap->GetTileConst(position);

    if (!seaMap->scannedWithRadar)
        return GetTileChar(tile, fogOfWar);
    else if (!fogOfWar)
        return GetTileChar(tile, false);

    return GetTileChar(tile, !seaMap->IsScanned(position));
}

void FrameRender::AddMapRow(const std::shared_ptr<SeaMap> seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar)
{
    const int width = seaMap->size.first;

    for (int x = 0; x < width; x++)
    {
        std::pair<int, int> position = std::pair<int, int>(x, y);

        ConsoleTextAttribute attribute = MapTextAttribute;
        if (actionPosition == position && fogOfWar)
            attribute = PointedAtTileAttribute;

        _text->Append(attribute, GetTileChar(seaMap, position, fogOfWar));
    }
}

void FrameRender::AddPlayerTextsLine()
{
    AddText(PlayerTextsAttribute, CurrentPlayerMapText);

    const int GapBetweenPlayerTextsLength = mapSize.first + GapBetweenMaps.length() - CurrentPlayerMapText.length();
    AddText(PlayerTextsAttribute, std::string(GapBetweenPlayerTextsLength, ' '));

    AddText(PlayerTextsAttribute, CurrentEnemyMapText);
    AddChar(PlayerTextsAttribute, '\n');
}

void FrameRender::AddText(const ConsoleTextAttribute attribute, const std::string& text)
{
    _text->Append(attribute, text);
}

void FrameRender::AddText(const std::string& text)
{
    _text->Append(text);
}

void FrameRender::AddChar(const ConsoleTextAttribute attribute, const char character)
{
    _text->Append(attribute, character);
}

void FrameRender::AddChar(const char character)
{
    _text->Append(character);
}

void FrameRender::AddPlayersRadarScansLeftText(const std::shared_ptr<Player> attackingPlayer)
{
    AddText(PlayerRadarScansLeftText);
    AddText(std::to_string(attackingPlayer->GetRadarsLeft()));
}

void FrameRender::AddPlayersMapsLines(const std::shared_ptr<Player> attackingPlayer, const std::shared_ptr<Player> attackedPlayer, const std::pair<int, int> actionPosition)
{
    const std::shared_ptr<SeaMap> attackingPlayerMap = attackingPlayer->GetMap();
    const std::shared_ptr<SeaMap> attackedPlayerMap = attackedPlayer->GetMap();

    for (int y = 0; y < mapSize.second; y++)
    {
        AddMapRow(attackingPlayerMap, actionPosition, y, false);
        AddText(MapTextAttribute, GapBetweenMaps);
        AddMapRow(attackedPlayerMap, actionPosition, y, !_areBothPlayersBots);
        AddChar(MapTextAttribute, '\n');
    }
}

void FrameRender::AddTipLine()
{
    AddText(TipTextAttribute, TipText);
}