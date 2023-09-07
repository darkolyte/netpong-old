#pragma once

#include "State.h"
#include "Audio.h"
#include "Maths.h"

namespace NetPong
{
    class ExampleState : public Engine::State
    {
    public:
        ExampleState(SDL_Renderer *&renderer);

        void Init() override;
        void Update() override;
        void Render() override;

        void Delete() override;

    private:
        Vec2 GenerateFrame(Vec2 previous_frame);

    private:
        SDL_Renderer *m_renderer;

        Engine::SDL_Audio m_bgm;
        Vec2 m_particles[250];
        int m_particle_count;
    };
}