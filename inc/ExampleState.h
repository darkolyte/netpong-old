#pragma once

#include "State.h"
#include "Audio.h"
#include "Maths.h"

namespace NetPong
{
    struct ExampleStateRes
    {
        Engine::SDL_Audio bgm = {"res/Audio/rain.wav"};

        Vec2 GenerateFrame(SDL_Renderer *renderer, Vec2 previous_frame);
    };

    class ExampleState : public Engine::State
    {
    public:
        ExampleState();

        void Init() override;
        void Update() override;
        void Render() const override;

        void Delete() override;

    private:
        ExampleStateRes res;
    };
}