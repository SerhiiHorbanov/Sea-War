#pragma once
#include <memory>
#include "GameState.h"
#include "SeaWar.h"

class Game
{
private:
    std::shared_ptr<GameState> _currentState;
    std::shared_ptr<GameState> _nextState;

public:
    Game() :
        _currentState(std::shared_ptr<GameState>((GameState*)new SeaWar()))
    {}
    
    void Run();
    
    void SetNextState(std::shared_ptr<GameState> nextState);
    void CheckAndHandleStateChange();
    
private:
    bool GameContinues() const;
};
