#include "Game.h"

void Game::Run()
{
    _currentState->Initialization();

    while (GameContinues())
        _currentState->RunFrame(this);
}

void Game::SetNextState(std::shared_ptr<GameState> nextState)
{
    _nextState = nextState;
}

void Game::CheckAndHandleStateChange()
{
    if (!_nextState)
        return;

    _currentState = _nextState;
    _currentState->Initialization();
}

bool Game::GameContinues() const
{
    return _currentState->GameContinues();
}
