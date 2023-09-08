#pragma once

#include <SDL3/SDL.h>

#include "State.h"
#include "Audio.h"
#include "Maths.h"
#include "Texture.h"

namespace NetPong
{
    class MenuState : public Engine::State
    {
    public:
        MenuState(SDL_Renderer *&renderer);

        void Init() override;
        void Update() override;
        void Render() override;

        void Delete() override;

    private:
        bool CursorOverJoinButton();
        bool CursorOverExitButton();

    private:
        SDL_Renderer *m_renderer;

        Engine::SDL_Audio m_bgm;
        Engine::Texture m_title_text;
        Engine::Texture m_join_button;
        Engine::Texture m_exit_button;
    };
}