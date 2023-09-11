#pragma once

#include <SDL3/SDL.h>

#include "Application.h"
#include "State.h"
#include "StateManager.h"
#include "Audio.h"
#include "Maths.h"
#include "Texture.h"

namespace NetPong
{
    class MenuState : public Engine::State
    {
    public:
        MenuState(SDL_Renderer *&renderer, Engine::StateManager &state_stack, Engine::Application *app_ref);
        ~MenuState();

        void Init() override;
        void Update() override;
        void Render() override;

        void Delete() override;

    private:
        bool CursorOverButton(Engine::Texture &button);
        void UpdateButtonTexture(Engine::Texture &button, Vec2 pos, int font_size, Uint8 alpha = 255);

    private:
        Engine::Application *m_app_ref;

        SDL_Renderer *m_renderer;
        Engine::StateManager *m_state_stack;

        Engine::SDL_Audio *m_bgm;
        Engine::Texture m_title_text;
        Engine::Texture m_join_button;
        Engine::Texture m_host_button;
        Engine::Texture m_exit_button;

        bool m_was_over_host;
        bool m_was_over_join;
        bool m_was_over_exit;
    };
}