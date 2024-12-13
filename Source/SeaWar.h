 #pragma once
#include "GameState.h"
#include "Render/FrameRender.h"
#include "Player.h"

class SeaWar : GameState
{

private:
    enum class TurnActionType
    {
        None,
        Shoot,
        RadarScan,
    };

    std::shared_ptr<Player> _firstPlayer;
    std::shared_ptr<Player> _secondPlayer;

    bool isFirstPlayersTurn;

    std::pair<int, int> _mapCursorPosition;
    TurnActionType _actionType;

public:
    SeaWar() = default;

    void Initialization() override;
    
    bool GameContinues() const override;
    
    void Render() override;
    void Input() override;
    void Update(Game* handler) override;

    void SetRandomSeed();
    void InitializePlayers();
    
    FrameRender GenerateImage() const;

    char EnterInput() const;
    void ProcessInput(const char input);
    void TryMoveActionPosition(const std::pair<int, int> delta);

    void HandlePlayerActions();
    void RegeneratePlayerMaps() const;
    void CheckAndHandleWin(std::shared_ptr<Player> winner, std::shared_ptr<Player> loser) const;

    void PerformBotAction();
    void PerformAction(const TurnActionType type, const std::pair<int, int> position);
    
    void Scan(const std::pair<int, int> position) const; 
    void Shoot(const std::pair<int, int> position);
    
    void SwapActingPlayer();

    bool AreBothPlayersBots() const;
    std::shared_ptr<Player> GetActingPlayer() const;
    std::shared_ptr<Player> GetWaitingPlayer() const;
};
