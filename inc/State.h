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
        virtual void Update() = 0;
        virtual void Render() const = 0;

        virtual void Delete() = 0;
    };
}