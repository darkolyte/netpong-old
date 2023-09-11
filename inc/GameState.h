#pragma once

#include <string>

#include "State.h"
#include "StateManager.h"

namespace NetPong
{
    class GameState : public Engine::State
    {
    public:
        GameState(SDL_Renderer *&renderer, Engine::StateManager &state_stack);
        GameState(SDL_Renderer *&renderer, Engine::StateManager *&state_stack);

        void Init() override;
        void Update() override;
        void Render() override;

        void Delete() override;

    private:
        SDL_Renderer *m_renderer;
        Engine::StateManager *m_state_stack;
    };
}