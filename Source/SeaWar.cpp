#include "SeaWar.h"
#include <conio.h>
#include "Render/FrameRender.h"
//#include "Render/ConsoleTextAttribute.h"

const char DefaultInput = ' ';

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
    ConsoleTextAttribute::InitializeSTDHandle();
}

void SeaWar::SetRandomSeed()
{
    std::srand(time(NULL));
}

void SeaWar::InitializePlayers()
{
    P1Map.reset();
    P2Map.reset();
    P1Map = Player::CreateNewPlayer(false);
    P2Map = Player::CreateNewPlayer(false);
}

void SeaWar::SetAttackingAndAttackedMaps()
{
    AttackingPlayer = P1Map;
    AttackedPlayer = P2Map;
}

void SeaWar::Render() const
{
    const FrameRender render = GenerateImage();
    render.Display();
}

FrameRender SeaWar::GenerateImage() const
{
    FrameRender render = FrameRender();
    render.Render(AttackingPlayer, AttackedPlayer, actionPosition);
    return render;
}

void SeaWar::Input()
{
    const char input = EnterInput();
    ProcessInput(input);
}

char SeaWar::EnterInput() const
{
    if (AreBothPlayersBots())
        return DefaultInput;
    return _getch();
}

void SeaWar::ProcessInput(const char input)
{
    actionType = TurnActionType::None;

    switch (input)
    {
    case 'w':
        TryMoveActionPosition({ 0, -1 });
        break;
    case 's':
        TryMoveActionPosition({ 0, 1 });
        break;
    case 'a':
        TryMoveActionPosition({ -1, 0 });
        break;
    case 'd':
        TryMoveActionPosition({ 1, 0 });
        break;
    case 'e':
        actionType = TurnActionType::Shoot;
        break;
    case 'r':
        actionType = TurnActionType::RadarScan;
        break;
    }
}

void SeaWar::TryMoveActionPosition(const std::pair<int, int> delta)
{
    const std::pair<int, int> newPosition = { delta.first + actionPosition.first, delta.second + actionPosition.second };

    if (AttackedPlayer->GetMap()->IsInBounds(newPosition))
        actionPosition = newPosition;
}

void SeaWar::Update()
{
    HandlePlayerActions();
}

void SeaWar::HandlePlayerActions()
{
    PerformAction(actionType, actionPosition);

    if (!AttackingPlayer->IsBot())
        return;

    do
    {
        const std::pair<int, int> botActionPosition = AttackedPlayer->GetMap()->GetRandomNotShotTile();
        PerformAction(TurnActionType::Shoot, botActionPosition);
    } while (AttackingPlayer->IsBot() && !AttackedPlayer->IsBot());
}

void SeaWar::PerformAction(const TurnActionType actionType, const std::pair<int, int> position)
{
    switch (actionType)
    {
    case TurnActionType::Shoot:
        Shoot(position);
        break;
    case TurnActionType::RadarScan:
        Scan(position);
        break;
    }
}

void SeaWar::Shoot(const std::pair<int, int> position)
{
    const ShootingResult shootingResult = AttackedPlayer->ShootAtPosition(position);

    if (shootingResult == ShootingResult::Miss)
        SwapAttackingPlayer();
}

void SeaWar::SwapAttackingPlayer()
{
    std::swap(AttackingPlayer, AttackedPlayer);
}

void SeaWar::Scan(const std::pair<int, int> position)
{
    if (AttackingPlayer->TryConsumeRadarScan())
        AttackedPlayer->ScanAtPosition(position);
}

bool SeaWar::AreBothPlayersBots() const
{
    return P1Map->IsBot() && P2Map->IsBot();
}

bool SeaWar::GameContinues() const
{
    return !P1Map->HasLost() && !P2Map->HasLost();
}