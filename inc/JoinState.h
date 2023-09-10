#pragma once

#include <SDL3/SDL.h>

#include <string>

#include "State.h"
#include "StateManager.h"

#include "Maths.h"
#include "Texture.h"

namespace NetPong
{
    class JoinState : public Engine::State
    {
    public:
        JoinState(SDL_Renderer *&renderer, Engine::StateManager &state_stack);
        JoinState(SDL_Renderer *&renderer, Engine::StateManager *&state_stack);

        void Init() override;
        void Update() override;
        void Render() override;

        void Delete() override;

    private:
        SDL_Renderer *m_renderer;
        Engine::StateManager *m_state_stack;

        Engine::Texture m_heading_text;
        Engine::Texture m_input_text;

        std::string m_input;

        bool m_render_required;
    };
}