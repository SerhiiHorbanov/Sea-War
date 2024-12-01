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

public:
    FrameRender() :
        _text(std::shared_ptr<MultiAttributedText>(new MultiAttributedText())),        
        _areBothPlayersBots()
    {}

    void Render(const std::shared_ptr<Player> attackingPlayer, const std::shared_ptr<Player> attackedPlayer, const std::pair<int, int> actionPosition);
    void Display() const;

private:
    void InitializeAreBothPlayersBots(const std::shared_ptr<Player> attackingPlayer, const std::shared_ptr<Player> attackedPlayer);

    void ReserveMemory();
    int EvaluateImageLength() const;

    void AddPlayerTextsLine();
    void AddPlayersMapsLines(const std::shared_ptr<Player> attackingPlayer, const std::shared_ptr<Player> attackedPlayer, const std::pair<int, int> actionPosition);
    void AddTipLine();
    void AddPlayersRadarScansLeftText(const std::shared_ptr<Player> attackingPlayer);

    void AddMapRow(const std::shared_ptr<SeaMap> seaMap, const std::pair<int, int> actionPosition, const int y, const bool fogOfWar);

    void AddText(const ConsoleTextAttribute attribute, const std::string& text);
    void AddText(const std::string& text);
    void AddChar(const ConsoleTextAttribute attribute, const char character);
    void AddChar(const char character);
};