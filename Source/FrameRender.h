#pragma once
#include <string>
#include "SeaMap.h"

struct FrameRender
{
public:
    std::string text;

    FrameRender() = default;

    static FrameRender Render(const SeaMap& AttackingPlayer, const SeaMap& AttackedPlayer);
    void Display() const;

    void ReserveMemory();
    int EvaluateImageLength() const;

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(const SeaMap& AttackingPlayer, const SeaMap& AttackedPlayer);
};