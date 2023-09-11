#pragma once

#include <SDL3/SDL.h>

#include "StateManager.h"

namespace Engine
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Open();
        void Close();

    private:
        void Init();

    private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;

        bool m_running;

        Engine::StateManager m_state_stack;
    };
}