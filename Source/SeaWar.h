 #pragma once
#include <string>
#include "Render/FrameRender.h"
#include "Player.h"

class SeaWar
{
    enum class TurnActionType
    {
        None,
        Shoot,
        RadarScan,
    };

    std::shared_ptr<Player> _firstPlayer;
    std::shared_ptr<Player> _secondPlayer;
    std::shared_ptr<Player> _actingPlayer;
    std::shared_ptr<Player> _inactivePlayer;

    std::pair<int, int> _mapCursorPosition;
    TurnActionType _actionType;

public:
    SeaWar() = default;
    void Run();

private:
    void Initialization();

    bool GameContinues() const;

    void Render() const;
    void Input();
    void Update();

    static void SetRandomSeed();
    void InitializePlayers();
    
    FrameRender GenerateImage() const;

    char EnterInput() const;
    void ProcessInput(const char input);
    void TryMoveActionPosition(const std::pair<int, int> delta);

    void HandlePlayerActions();
    void RegeneratePlayerMaps() const;
    void CheckAndHandleWin(std::shared_ptr<Player> winner, std::shared_ptr<Player> loser) const;

    void PerformAction(const TurnActionType type, const std::pair<int, int> position);

    void Scan(const std::pair<int, int> position) const; 
    void Shoot(const std::pair<int, int> position);
    
    void SwapActingPlayer();

    bool AreBothPlayersBots() const;
};