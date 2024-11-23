#pragma once
#include <string>
#include "SeaMap.h"

struct FrameRender
{
public:
    std::string text;

    FrameRender() = default;

    static FrameRender Render(SeaMap& AttackingPlayer, SeaMap& AttackedPlayer);
    void Display();

    void ReserveMemory();
    int EvaluateImageLength();

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(SeaMap& AttackingPlayer, SeaMap& AttackedPlayer);
};