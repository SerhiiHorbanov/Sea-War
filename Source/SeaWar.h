 #pragma once
#include <string>
#include "FrameRender.h"
#include "SeaMap.h"

class SeaWar
{
    enum class TurnActionType
    {
        None,
        Shoot,
        RadarScan,
    };

    std::unique_ptr<SeaMap> P1Map;
    std::unique_ptr<SeaMap> P2Map;
    SeaMap* AttackingPlayer;
    SeaMap* AttackedPlayer;

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
    void SetRandomSeaMaps();
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