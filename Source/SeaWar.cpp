#include "SeaWar.h"
#include <conio.h>
#include "Render/FrameRender.h"

constexpr char DefaultInput = ' ';
constexpr int RoundWinsRequiredForGameWin = 3;

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
    ConsoleTextAttribute::InitializeStdHandle();
}

void SeaWar::SetRandomSeed()
{
    std::srand(time(NULL));
}

void SeaWar::InitializePlayers()
{
    _firstPlayer.reset();
    _secondPlayer.reset();
    _firstPlayer = Player::CreateNewPlayer(false);
    _secondPlayer = Player::CreateNewPlayer(false);
}

void SeaWar::SetAttackingAndAttackedMaps()
{
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
    render.Render(_actingPlayer, _inactivePlayer, _mapCursorPosition);
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
    const std::pair<int, int> newPosition = { delta.first + _mapCursorPosition.first, delta.second + _mapCursorPosition.second };

    if (_inactivePlayer->GetMap()->IsInBounds(newPosition))
        _mapCursorPosition = newPosition;
}

void SeaWar::Update()
{
    HandlePlayerActions();
    CheckForWinner();
}

void SeaWar::HandlePlayerActions()
{
    PerformAction(_actionType, _mapCursorPosition);

    if (!_actingPlayer->IsBot())
        return;

    do
    {
        const std::pair<int, int> botActionPosition = _inactivePlayer->GetMap()->GetRandomNotShotTile();
        PerformAction(TurnActionType::Shoot, botActionPosition);
    } while (_actingPlayer->IsBot() && !_inactivePlayer->IsBot());
}

void SeaWar::ReGeneratePlayerMaps() const
{
    _firstPlayer->RegenerateMap();
    _secondPlayer->RegenerateMap();
}

void SeaWar::CheckPlayerWon(std::shared_ptr<Player> winner, std::shared_ptr<Player> loser) const
{
    if (loser->HasLost())
    {
        winner->Win();
        ReGeneratePlayerMaps();
    }
}

void SeaWar::CheckForWinner() const
{
    CheckPlayerWon(_actingPlayer, _inactivePlayer);
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
        SwapAttackingPlayer();
}

void SeaWar::SwapAttackingPlayer()
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

bool SeaWar::GameContinues() const
{
    bool firstPlayerWonGame = _firstPlayer->GetWins() < RoundWinsRequiredForGameWin;
    bool secondPlayerWonGame = _secondPlayer->GetWins() < RoundWinsRequiredForGameWin;
    
    return  firstPlayerWonGame || secondPlayerWonGame;
}