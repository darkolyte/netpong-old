#include <iostream>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Maths.h"
#include "State.h"
#include "StateManager.h"
#include "Texture.h"
#include "ExampleState.h"

int main(int argc, char *args[])
{
    /* Initialized required libraries */

    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cout << "Failed to initialize SDL Subsystems!" << std::endl;
        return 1;
    }

    std::cout << "SDL Subsystems Initialized!" << std::endl;

    if (TTF_Init() == -1)
    {
        std::cout << "Failed to initialize SDL TTF!" << std::endl;
        return 1;
    }

    std::cout << "SDL TTF Initialized!" << std::endl;

    /* Create Window */

    SDL_Window *window = SDL_CreateWindow("NetPong: Test Window", 900, 900, SDL_EVENT_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Failed to create window!" << std::endl;
        return 1;
    }

    /* Create Renderer */

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        std::cout << "Failed to create renderer!" << std::endl;
        return 1;
    }

    bool running = true;

    SDL_Event e;

    auto state_manager = Engine::StateManager::GetInstance();

    std::shared_ptr<NetPong::ExampleState> test_scene = std::make_shared<NetPong::ExampleState>(renderer);

    state_manager.PushNewState(test_scene);

    while (running)
    {

        std::shared_ptr<Engine::State> current = state_manager.GetCurrentState();
        current->Update();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        current->Render();

        SDL_RenderPresent(renderer);
    }
}