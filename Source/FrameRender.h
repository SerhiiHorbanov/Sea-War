#pragma once
#include <string>
#include "MultiAttributedText.h"
#include "Player.h"

struct FrameRender
{
public:
    MultiAttributedText text;

    FrameRender() = default;

    static FrameRender Render(const Player& attackingPlayer, const Player& attackedPlayer, const std::pair<int, int> actionPosition);
    void Display() const;

    void ReserveMemory();
    int EvaluateImageLength() const;

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(const Player& attackingPlayer, const Player& attackedPlayer, const std::pair<int, int> actionPosition);
    void AddTipLine();

    void AddMapRow(const SeaMap& seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar);
};