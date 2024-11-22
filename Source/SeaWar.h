#pragma once
#include <string>
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

    std::string GetImage();
    void DisplayImage(std::string image);
    int EvaluateImageLength();
    std::string GetMapRowText(const SeaMap& seaMap, const int y);

    std::string GetInput();
    void ProcessInput(const std::string& input);

    void TryShooting();
};

