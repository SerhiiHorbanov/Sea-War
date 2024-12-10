#include "SeaWar.h"
#include <conio.h>
#include "Render/FrameRender.h"
#include "Render/RenderOfInt.h"
#include "Render/RenderOfSeaMap.h"
#include "Render/RenderOfText.h"

const std::string TipText = "press W/A/S/D to move. press E to shoot. press R to scan with radar\n";
const std::string PlayerRadarScansLeftText = "radar scans left:";

const ConsoleTextAttribute TipTextAttribute = ConsoleTextAttribute(ConsoleColor::LightGreen);

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
    ConsoleTextAttribute::InitializeStdHandle();
}

bool SeaWar::GameContinues() const
{
    bool firstPlayerWonGame = _firstPlayer->HasWonGame();
    bool secondPlayerWonGame = _secondPlayer->HasWonGame();
    
    return  !firstPlayerWonGame && !secondPlayerWonGame;
}

void SeaWar::SetRandomSeed()
{
    std::srand(time(NULL));
}

void SeaWar::InitializePlayers()
{
    _firstPlayer = Player::CreateNewPlayer(false);
    _secondPlayer = Player::CreateNewPlayer(false);
    
    _actingPlayer = _firstPlayer;
    _inactivePlayer = _secondPlayer;
}

void SeaWar::Render() const
{
    const FrameRender render = GenerateImage();
    render.Display();
}

FrameRender SeaWar::GenerateImage() const
{
    FrameRender render = FrameRender();

    if (_inactivePlayer->IsBot())
    {
        render.AddRenderObject<RenderOfSeaMap>(_actingPlayer->GetMap(), false, std::pair(-1, -1));
        render.AddRenderObject<RenderOfText>("\n");
    }

    const bool useFogOfWarOnMapOfInactivePlayer = !AreBothPlayersBots();
    render.AddRenderObject<RenderOfSeaMap>(_inactivePlayer->GetMap(), useFogOfWarOnMapOfInactivePlayer, _mapCursorPosition);
    render.AddRenderObject<RenderOfText>(TipText, TipTextAttribute);
    render.AddRenderObject<RenderOfText>(PlayerRadarScansLeftText, TipTextAttribute);
    render.AddRenderObject<RenderOfInt>(_actingPlayer->GetRadarsLeft(), TipTextAttribute);
    render.Render();
    
    return render;
}

void SeaWar::Input()
{
    const char input = EnterInput();
    ProcessInput(input);
}

char SeaWar::EnterInput() const
{
    return _getch();
}

void SeaWar::ProcessInput(const char input)
{
    _actionType = TurnActionType::None;

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
        _actionType = TurnActionType::Shoot;
        break;
    case 'r':
        _actionType = TurnActionType::RadarScan;
        break;
    }
}

void SeaWar::TryMoveActionPosition(const std::pair<int, int> delta)
{
    const std::pair newPosition = { delta.first + _mapCursorPosition.first, delta.second + _mapCursorPosition.second };

    if (_inactivePlayer->GetMap()->IsInBounds(newPosition))
        _mapCursorPosition = newPosition;
}

void SeaWar::Update()
{
    HandlePlayerActions();
    CheckAndHandleWin(_actingPlayer, _inactivePlayer);
}

void SeaWar::HandlePlayerActions()
{
    if (_actingPlayer->IsBot())
    {
        PerformBotAction();
        return;
    }
    
    PerformAction(_actionType, _mapCursorPosition);
    
    while (_actingPlayer->IsBot() && !_inactivePlayer->IsBot())
        PerformBotAction();
}



void SeaWar::RegeneratePlayerMaps() const
{
    _firstPlayer->RegenerateMap();
    _secondPlayer->RegenerateMap();
}

void SeaWar::CheckAndHandleWin(std::shared_ptr<Player> winner, std::shared_ptr<Player> loser) const
{
    if (loser->HasLostRound())
    {
        winner->WinRound();
        RegeneratePlayerMaps();
    }
}

void SeaWar::PerformBotAction()
{
    const std::pair botAttackPosition = _inactivePlayer->GetMap()->GetRandomNotShotTile();
    PerformAction(TurnActionType::Shoot, botAttackPosition);
}

void SeaWar::PerformAction(const TurnActionType type, const std::pair<int, int> position)
{
    switch (type)
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
    const ShootingResult shootingResult = _inactivePlayer->ShootAtPosition(position);

    if (shootingResult == ShootingResult::Miss)
        SwapActingPlayer();
}

void SeaWar::SwapActingPlayer()
{
    std::swap(_actingPlayer, _inactivePlayer);
}

void SeaWar::Scan(const std::pair<int, int> position) const
{
    if (_actingPlayer->TryConsumeRadarScan())
        _inactivePlayer->ScanAtPosition(position);
}

bool SeaWar::AreBothPlayersBots() const
{
    return _firstPlayer->IsBot() && _secondPlayer->IsBot();
}