#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>

#include "Audio.h"

struct Vec2
{
    int x;
    int y;
};

Vec2 PlayIntroSequence(SDL_Renderer *renderer, Vec2 p_start);

int main(int argc, char *args[])
{
    /* Initialized required libraries */

    if (SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        std::cout << "Failed to initialize SDL Subsystems!" << std::endl;
        return 1;
    }

    std::cout << "SDL Video Subsystem Initialized!" << std::endl;

    if (TTF_Init() == -1)
    {
        std::cout << "Failed to initialize SDL TTF!" << std::endl;
        return 1;
    }

    std::cout << "SDL TTF Initialized!" << std::endl;

    Engine::SDL_Audio audio = {"res/Audio/rain.wav"};
    audio.SetupDevice();

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

    Vec2 starts[250];

    int starts_size = sizeof(starts) / sizeof(starts[0]);

    for (int i = 0; i < starts_size; i++)
    {
        starts[i].x = rand() % 900;
        starts[i].y = rand() % 900;
    }

    audio.Play();

    while (running)
    {
        if (!audio.IsPlaying())
        {
            audio.Play();
        }

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

        for (int i = 0; i < starts_size; i++)
        {
            starts[i] = PlayIntroSequence(renderer, starts[i]);
        }

        SDL_RenderPresent(renderer);
    }
}

Vec2 PlayIntroSequence(SDL_Renderer *renderer, Vec2 p_start)
{
    int x = p_start.x - rand() % 5;
    int y = p_start.y - rand() % 5;

    if (x > 900 || y > 900)
    {
        x = rand() % 900;
        y = rand() % 900;
    }

    int end = x + 5 + rand() % 60;

    int fade_x = x - 150 + rand() % 100;
    int fade_y = y - 150 + rand() % 100;

    int r = rand() % 20;
    int g = rand() % 20;
    int b = 40 + rand() % 255;

    SDL_SetRenderDrawColor(renderer, r / 2, g / 2, b / 2, 128);

    for (; fade_x < x; fade_x++, fade_y++)
    {
        SDL_RenderPoint(renderer, fade_x, fade_y);
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);

    for (; x < end; x++, y++)
    {
        SDL_RenderPoint(renderer, x, y);
    }

    SDL_DelayNS(75000);

    return {x, y};
}