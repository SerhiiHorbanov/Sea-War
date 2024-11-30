#pragma once
#include <string>
#include <memory>
#include "MultiAttributedText.h"
#include "Player.h"

struct FrameRender
{
private:
    std::shared_ptr<MultiAttributedText> _text;
    bool _areBothPlayersBots;

    FrameRender() :
        _text(std::shared_ptr<MultiAttributedText>(new MultiAttributedText())),        
        _areBothPlayersBots()
    {}

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
    void AddPlayersRadarScansLeftText(const Player& attackingPlayer);

    void AddMapRow(const SeaMap& seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar);

    void AddText(const ConsoleTextAttribute attribute, const std::string& text);
    void AddText(const std::string& text);
    void AddChar(const ConsoleTextAttribute attribute, const char character);
    void AddChar(const char character);
};