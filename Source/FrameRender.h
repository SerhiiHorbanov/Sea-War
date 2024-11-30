#pragma once
#include <string>
#include "MultiAttributedText.h"
#include "Player.h"

struct FrameRender
{
private:
    MultiAttributedText text;
    bool areBothPlayersBots;

    FrameRender() = default;

public:
    static FrameRender Render(const Player& attackingPlayer, const Player& attackedPlayer, const std::pair<int, int> actionPosition);
    void Display() const;

private:
    void InitializeAreBothPlayersBots(const Player& attackingPlayer, const Player& attackedPlayer);

    void ReserveMemory();
    int EvaluateImageLength() const;

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(const Player& attackingPlayer, const Player& attackedPlayer, const std::pair<int, int> actionPosition);
    void AddTipLine();

    void AddMapRow(const SeaMap& seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar);
};