#include "SeaWar.h"
#include <iostream>
#include <sstream>
#include "FrameRender.h"

void SeaWar::Run()
{
    Initialization();

    while (GameContinues())
    {
        Render();
        Input();
        Update();
    }
}

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
    const FrameRender render = GenerateImage();
    render.Display();
}

FrameRender SeaWar::GenerateImage()
{
    return FrameRender::Render(*AttackingPlayer, *AttackedPlayer);
}

void SeaWar::Input()
{
    const std::string input = EnterInput();
    ProcessInput(input);
}

std::string SeaWar::EnterInput()
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
    if (!isValidShootingPosition)
        return;

    const MapShootingResult shootingResult = AttackedPlayer->ShootAtTile(shootingPosition);

    if (shootingResult == MapShootingResult::ShipShot)
        return;

    std::swap(AttackingPlayer, AttackedPlayer);
}

bool SeaWar::GameContinues()
{
    return P1Map.AnyShipsLeft && P2Map.AnyShipsLeft;
}