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
    InitializePlayers();
    SetAttackingAndAttackedMaps();
}

void SeaWar::SetRandomSeed()
{
    std::srand(time(NULL));
}

void SeaWar::InitializePlayers()
{
    P1Map.reset();
    P2Map.reset();
    P1Map = Player::CreateNewPlayer();
    P2Map = Player::CreateNewPlayer();
}

void SeaWar::SetAttackingAndAttackedMaps()
{
    AttackingPlayer = P1Map.get();
    AttackedPlayer = P2Map.get();
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

    actionType = GetActionTypeByChar(stream.get());
    isValidActionPosition = true;

    try
    {
        std::string numberText;
        std::getline(stream, numberText, ',');
        const int x = std::stoi(numberText) - 1;
        std::getline(stream, numberText);
        const int y = std::stoi(numberText) - 1;

        actionPosition = std::pair<int, int>(x, y);
    }
    catch (std::exception exception)
    {
        isValidActionPosition = false;
    }
    
    if (!AttackedPlayer->GetMap().IsInBounds(actionPosition))
        isValidActionPosition = false;
}

void SeaWar::Update()
{
    TryPerformAction();
}

void SeaWar::TryPerformAction()
{
    if (!isValidActionPosition)
        return;

    switch (actionType)
    {
    case TurnActionType::Shoot:
        Shoot();
        break;
    case TurnActionType::RadarScan:
        Scan();
        break;
    }
}

void SeaWar::Shoot()
{
    const ShootingResult shootingResult = AttackedPlayer->ShootAtPosition(actionPosition);

    if (shootingResult == ShootingResult::Miss)
        SwapAttackingPlayer();
}

void SeaWar::SwapAttackingPlayer()
{
    std::swap(AttackingPlayer, AttackedPlayer);
}

SeaWar::TurnActionType SeaWar::GetActionTypeByChar(char character)
{
    switch (character)
    {
    case 'r':
        return TurnActionType::RadarScan;
    case 's':
        return TurnActionType::Shoot;
    }
    return TurnActionType::None;
}

void SeaWar::Scan()
{
    AttackedPlayer->TryScanAtPosition(actionPosition);
}

bool SeaWar::GameContinues()
{
    return !P1Map->HasLost() && !P2Map->HasLost();
}