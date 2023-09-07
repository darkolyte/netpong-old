#pragma once

#include <vector>
#include <memory>

#include "State.h"

namespace Engine
{
    // Singleton class to manage states
    class StateManager
    {
    public:
        static StateManager &GetInstance();
        std::shared_ptr<State> GetCurrentState();

        void PopCurrentState();
        void PushNewState(const std::shared_ptr<State> &state);

    private:
        StateManager() {} // Private constructor, ie. cannot instantiate multiple instances of singleton
    private:
        std::vector<std::shared_ptr<State>> m_states;
    };
}