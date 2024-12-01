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

    std::shared_ptr<Player> P1Map;
    std::shared_ptr<Player> P2Map;
    std::shared_ptr<Player> AttackingPlayer;
    std::shared_ptr<Player> AttackedPlayer;

    std::pair<int, int> actionPosition;
    TurnActionType actionType;

public:
    void Run();

private:
    void Initialization();

    bool GameContinues() const;

    void Render() const;
    void Input();
    void Update();

    void SetRandomSeed();
    void InitializePlayers();
    void SetAttackingAndAttackedMaps();

    FrameRender GenerateImage() const;

    char EnterInput() const;
    void ProcessInput(const char input);
    void TryMoveActionPosition(const std::pair<int, int> delta);

    void HandlePlayerActions();

    void PerformAction(const TurnActionType type, const std::pair<int, int> position);

    void Scan(const std::pair<int, int> position) const; 
    void Shoot(const std::pair<int, int> position);
    
    void SwapAttackingPlayer();

    bool AreBothPlayersBots() const;
};