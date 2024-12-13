#pragma once

class Game;

class GameState
{
public:
    virtual ~GameState() = default;
    
    virtual void Initialization() = 0;
    
    virtual void Update(Game* handler) = 0;
    virtual void Render() = 0;
    virtual void Input() = 0;
    
    void RunFrame(Game* handler);
    
    virtual bool GameContinues() const = 0;
};
