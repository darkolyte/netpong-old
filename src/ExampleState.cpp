#include <random>

#include "ExampleState.h"
#include "Audio.h"

NetPong::ExampleState::ExampleState(SDL_Renderer *&renderer)
    : m_bgm("res/Audio/rain.wav")
{
    m_renderer = renderer;
}

void NetPong::ExampleState::Init()
{
    m_bgm.SetupDevice();

    m_particle_count = sizeof(m_particles) / sizeof(m_particles[0]);

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    std::uniform_int_distribution<int> distribution(0, 900);

    for (int i = 0; i < m_particle_count; i++)
    {
        m_particles[i].x = distribution(generator);
        m_particles[i].y = distribution(generator);
    }
}

void NetPong::ExampleState::Update()
{
    if (m_bgm.IsPlaying())
    {
        return;
    }
    m_bgm.Play();
}

void NetPong::ExampleState::Render()
{
    for (int i = 0; i < m_particle_count; i++)
    {
        m_particles[i] = GenerateFrame(m_particles[i]);
    }
}

void NetPong::ExampleState::Delete()
{
    return;
}

Vec2 NetPong::ExampleState::GenerateFrame(Vec2 previous_frame)
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());

    std::uniform_int_distribution<int> distribution1(-5, 5);  // Subtle change between frames
    std::uniform_int_distribution<int> distribution2(0, 900); // New position if out of frame
    std::uniform_int_distribution<int> distribution3(5, 50);  // Varied length of particle
    std::uniform_int_distribution<int> distribution4(0, 20);  // Varied fade particle
    std::uniform_int_distribution<int> distribution5(0, 255); // Color of particle

    int x = previous_frame.x + distribution1(generator);
    int y = previous_frame.y + distribution1(generator);

    if (x > 900 || y > 900)
    {
        x = distribution2(generator);
        y = distribution2(generator);
    }

    int end = x + distribution3(generator);

    int f = distribution4(generator);

    int fade_x = x - f;
    int fade_y = y - f;

    int r = distribution5(generator);
    int g = distribution5(generator);

    int b = distribution5(generator);

    SDL_SetRenderDrawColor(m_renderer, r / 2, g / 2, b / 2, 128);

    for (; fade_x < x; fade_x++, fade_y++)
    {
        SDL_RenderPoint(m_renderer, fade_x, fade_y);
    }

    SDL_SetRenderDrawColor(m_renderer, r, g, b, 255);

    for (; x < end; x++, y++)
    {
        SDL_RenderPoint(m_renderer, x, y);
    }

    SDL_DelayNS(175000);

    return {float(x), float(y)};
}