 #pragma once
#include <string>
#include "FrameRender.h"
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
    Player* AttackingPlayer;
    Player* AttackedPlayer;

    std::pair<int, int> actionPosition;
    TurnActionType actionType;

public:
    void Run();

private:
    void Initialization();

    bool GameContinues();

    void Render();
    void Input();
    void Update();

    void SetRandomSeed();
    void InitializePlayers();
    void SetAttackingAndAttackedMaps();

    FrameRender GenerateImage();

    char EnterInput();
    void ProcessInput(const char input);
    void TryMoveActionPosition(const std::pair<int, int> delta);

    void PerformAction(const TurnActionType actionType, const std::pair<int, int> position);

    

    void Scan(const std::pair<int, int> position); 
    void Shoot(const std::pair<int, int> position);
    
    void SwapAttackingPlayer();
};