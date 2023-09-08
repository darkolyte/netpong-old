#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "State.h"
#include "StateManager.h"
#include "MenuState.h"

#include "Application.h"

Engine::Application::Application()
    : m_window(nullptr), m_renderer(nullptr), m_running(false),
      m_state_stack(Engine::StateManager::GetInstance())
{
    Init();
}

Engine::Application::~Application()
{
    Close();
}

void Engine::Application::Init()
{
    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL Subsystems! Error: %s", SDL_GetError());
    }

    if (TTF_Init() == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize SDL TTF! Error: %s", TTF_GetError());
    }

    // Define H and W elsewhere
    m_window = SDL_CreateWindow("NetPong v.0.1.0", 900, 900, SDL_EVENT_WINDOW_SHOWN); // | SDL_WINDOW_BORDERLESS

    if (!m_window)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window! Error: %s", SDL_GetError());
    }

    m_renderer = SDL_CreateRenderer(m_window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create renderer! Error: %s", SDL_GetError());
    }
}

void Engine::Application::Open()
{
    m_running = true;

    SDL_Event e;

    std::shared_ptr<Engine::State> start_state = std::make_shared<NetPong::MenuState>(m_renderer);
    m_state_stack.PushNewState(start_state);

    std::shared_ptr<Engine::State> current;

    while (m_running)
    {
        current = m_state_stack.GetCurrentState();
        current->Update();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                m_running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        SDL_RenderClear(m_renderer);

        current->Render();

        SDL_RenderPresent(m_renderer);
    }
}

void Engine::Application::Close()
{
    // Cleanup everything
}