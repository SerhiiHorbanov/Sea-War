#pragma once
#include <string>
#include "Player.h"

struct FrameRender
{
public:
    std::string text;

    FrameRender() = default;

    static FrameRender Render(const Player& attackingPlayer, const Player& attackedPlayer);
    void Display() const;

    void ReserveMemory();
    int EvaluateImageLength() const;

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(const Player& attackingPlayer, const Player& attackedPlayer);
    void AddAskingPlayerForActionLine();
};