#include <memory>
#include <vector>

#include "State.h"
#include "StateManager.h"

std::shared_ptr<Engine::State> Engine::StateManager::GetCurrentState()
{
    if (m_states.empty())
        return nullptr;
    else
        return m_states.back();
}

void Engine::StateManager::PopCurrentState()
{
    m_states.back()->Delete();
    m_states.pop_back();
}

void Engine::StateManager::PushNewState(const std::shared_ptr<State> &state)
{
    m_states.push_back(state);
    state->Init();
}

Engine::StateManager &Engine::StateManager::GetInstance()
{
    static StateManager instance; // Singleton instance
    return instance;
}