#include "GameState.h"

NetPong::GameState::GameState(SDL_Renderer *&renderer, Engine::StateManager &state_stack)
    : m_renderer(renderer), m_state_stack(&state_stack)
{
}

NetPong::GameState::GameState(SDL_Renderer *&renderer, Engine::StateManager *&state_stack)
    : m_renderer(renderer), m_state_stack(state_stack)
{
}

void NetPong::GameState::GameState::Init()
{
    return;
}

void NetPong::GameState::GameState::Update()
{
    return;
}

void NetPong::GameState::GameState::Render()
{
    return;
}

void NetPong::GameState::GameState::Delete()
{
    return;
}