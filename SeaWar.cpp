#include "SeaWar.h"
#include <iostream>
#include <sstream>

const std::string CurrentPlayerMapText = "Your map:";
const std::string CurrentEnemyMapText = "Enemy map:";
const std::string GapBetweenMaps = "          ";
const std::string AskingPlayerWhereToShootText = "Where would you like to shoot?";

void SeaWar::Initialization()
{
    SetRandomSeed();
    SetRandomSeaMaps();
    SetAttackingAndAttackedMaps();
}

void SeaWar::SetRandomSeed()
{
    std::srand(time(NULL));
}

void SeaWar::SetRandomSeaMaps()
{
    P1Map = SeaMap::GenerateRandomSeaMap(mapSize);
    P2Map = SeaMap::GenerateRandomSeaMap(mapSize);
}

void SeaWar::SetAttackingAndAttackedMaps()
{
    AttackingPlayer = &P1Map;
    AttackedPlayer = &P2Map;
}

void SeaWar::Render()
{
    std::string newImage = GetImage();
    DisplayImage(newImage);
}

void SeaWar::DisplayImage(std::string image)
{
    std::system("cls");
    std::cout << image;
}

std::string SeaWar::GetImage()
{
    std::string result;
    const int reserving = EvaluateImageLength();
    result.reserve(reserving);

    result += CurrentPlayerMapText;
    const int GapBetweenPlayerTextsLength = mapSize.first + GapBetweenMaps.length() - CurrentPlayerMapText.length();
    result += std::string(GapBetweenPlayerTextsLength, ' ');
    result += CurrentEnemyMapText;
    result += '\n';

    for (int y = 0; y < mapSize.second; y++)
    {
        result += GetMapRowText(*AttackingPlayer, y);
        result += GapBetweenMaps;
        result += GetMapRowText(*AttackedPlayer, y);
        result += '\n';
    }

    return result;
}

int SeaWar::EvaluateImageLength()
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

std::string SeaWar::GetMapRowText(const SeaMap& seaMap, const int y)
{
    std::string result;
    result.reserve(seaMap.size.first);

    for (int x = 0; x < seaMap.size.first; x++)
    {
        const std::pair<int, int> position = std::pair<int, int>(x, y);

        result += seaMap.GetTileChar(position);
    }

    return result;
}

void SeaWar::Input()
{
    std::string input = GetInput();
    ProcessInput(input);
}

std::string SeaWar::GetInput()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void SeaWar::ProcessInput(const std::string& input)
{
    std::stringstream stream = std::stringstream(input);

    isValidShootingPosition = true;
    try
    {
        std::string numberText;
        std::getline(stream, numberText, ',');
        const int x = std::stoi(numberText) - 1;
        std::getline(stream, numberText);
        const int y = std::stoi(numberText) - 1;

        shootingPosition = std::pair<int, int>(x, y);
    }
    catch (std::exception exception)
    {
        isValidShootingPosition = false;
    }

    if (!AttackedPlayer->IsInBounds(shootingPosition))
        isValidShootingPosition = false;
}

void SeaWar::Update()
{
    TryShooting();
}

void SeaWar::TryShooting()
{
    if (isValidShootingPosition)
    {
        AttackedPlayer->ShootAtTile(shootingPosition);
        std::swap(AttackingPlayer, AttackedPlayer);
    }
}

bool SeaWar::GameContinues()
{
    return P1Map.AnyShipsLeft && P2Map.AnyShipsLeft;
}