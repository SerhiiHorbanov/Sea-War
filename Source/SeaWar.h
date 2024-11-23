#pragma once
#include <string>
#include "FrameRender.h"
#include "SeaMap.h"

class SeaWar
{
    SeaMap P1Map;
    SeaMap P2Map;
    SeaMap* AttackingPlayer;
    SeaMap* AttackedPlayer;

    bool isValidShootingPosition;
    std::pair<int, int> shootingPosition;

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

    void TryShooting();
    void Shoot();
    void SwapAttackingPlayer();
};

