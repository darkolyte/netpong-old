#pragma once

#include <SDL3/SDL.h>

namespace Engine
{
    // Base class for application states
    class State
    {
    public:
        virtual ~State() {} // Virtual destructor, ie. cannot instantiate interface

        virtual void Init() = 0;
        virtual void Update() = 0; // Handles any logic required for the state
        virtual void Render() = 0; // Handles rendering of current frame

        virtual void Delete() = 0;
    };
}