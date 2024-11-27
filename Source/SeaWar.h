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

    bool isValidActionPosition;
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

    std::string EnterInput();
    void ProcessInput(const std::string& input);
    static TurnActionType GetActionTypeByChar(const char character);

    void TryPerformAction();

    void Scan();
    void Shoot();
    
    void SwapAttackingPlayer();
};