#pragma once
#include <string>
#include "SeaMap.h"

struct Image
{
public:
    std::string text;

    Image() = default;

    static Image GenerateImage(SeaMap& AttackingPlayer, SeaMap& AttackedPlayer);
    void Display();

    void ReserveMemory();
    int EvaluateImageLength();

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(SeaMap& AttackingPlayer, SeaMap& AttackedPlayer);

};