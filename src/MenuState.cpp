#include <SDL3/SDL.h>

#include "State.h"
#include "Audio.h"
#include "Maths.h"
#include "Texture.h"

#include "MenuState.h"
#include "JoinState.h"

NetPong::MenuState::MenuState(SDL_Renderer *&renderer, Engine::StateManager &state_stack)
    : m_renderer(renderer), m_state_stack(&state_stack), m_bgm(nullptr) {}

NetPong::MenuState::~MenuState()
{
    if (m_bgm)
    {
        m_bgm->Delete();
        m_bgm = nullptr;
    }
    m_renderer = nullptr;
    m_state_stack = nullptr;
}

void NetPong::MenuState::Init()
{
    if (m_bgm)
    {
        m_bgm->Delete();
        m_bgm = nullptr;
    }

    m_bgm = new Engine::SDL_Audio("res/Audio/rain.wav");

    m_bgm->SetupDevice();

    m_title_text.LoadText(m_renderer, "NetPong", {255, 255, 255, 255}, 92);
    m_title_text.SetPosition(900 / 2 - (m_title_text.GetSize().w / 2), 900 / 8);

    m_host_button.LoadText(m_renderer, "Host", {255, 255, 255, 255}, 52);
    m_host_button.SetPosition(900 / 2 - (m_host_button.GetSize().w / 2), 400 - (m_host_button.GetSize().h / 2));

    m_join_button.LoadText(m_renderer, "Join", {255, 255, 255, 255}, 52);
    m_join_button.SetPosition(900 / 2 - (m_join_button.GetSize().w / 2), 475 - (m_join_button.GetSize().h / 2));

    m_exit_button.LoadText(m_renderer, "Exit", {255, 255, 255, 255}, 52);
    m_exit_button.SetPosition(900 / 2 - (m_exit_button.GetSize().w / 2), 550 - (m_exit_button.GetSize().h / 2));
}

void NetPong::MenuState::Update()
{
    if (m_bgm && !m_bgm->IsPlaying())
    {
        m_bgm->Play();
    }

    if (CursorOverButton(m_host_button))
    {
        if (!m_was_over_host)
        {
            UpdateButtonTexture(m_host_button, {900 / 2, 400}, 56, 200);
            m_was_over_host = true;
        }

        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_MOUSE_BUTTON_UP)
            {
                m_bgm->Delete();
                m_bgm = nullptr;

                // std::shared_ptr<Engine::State> next_state = std::make_shared<NetPong::ExampleState>(m_renderer);
                // m_state_stack->PushNewState(next_state);
                return;
            }
        }
    }
    else
    {
        if (m_was_over_host)
        {
            UpdateButtonTexture(m_host_button, {900 / 2, 400}, 52);
            m_was_over_host = false;
        }
    }

    if (CursorOverButton(m_join_button))
    {
        if (!m_was_over_join)
        {
            UpdateButtonTexture(m_join_button, {900 / 2, 475}, 56, 200);
            m_was_over_join = true;
        }

        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_MOUSE_BUTTON_UP)
            {
                m_bgm->Delete();
                m_bgm = nullptr;

                std::shared_ptr<Engine::State> next_state = std::make_shared<NetPong::JoinState>(m_renderer, m_state_stack);
                m_state_stack->PushNewState(next_state);
                return;
            }
        }
    }
    else
    {
        if (m_was_over_join)
        {
            UpdateButtonTexture(m_join_button, {900 / 2, 475}, 52);
            m_was_over_join = false;
        }
    }

    if (CursorOverButton(m_exit_button))
    {
        if (!m_was_over_exit)
        {
            UpdateButtonTexture(m_exit_button, {900 / 2, 550}, 56, 200);
            m_was_over_exit = true;
        }

        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_MOUSE_BUTTON_UP)
            {
                while (m_state_stack->GetCurrentState())
                {
                    m_state_stack->PopCurrentState();
                }
            }
        }
    }
    else
    {
        if (m_was_over_exit)
        {
            UpdateButtonTexture(m_exit_button, {900 / 2, 550}, 52);
            m_was_over_exit = false;
        }
    }
}

void NetPong::MenuState::Render()
{
    m_title_text.Render(m_renderer);
    m_host_button.Render(m_renderer);
    m_join_button.Render(m_renderer);
    m_exit_button.Render(m_renderer);
}

void NetPong::MenuState::Delete()
{
    this->~MenuState();
}

bool NetPong::MenuState::CursorOverButton(Engine::Texture &button)
{
    Vec2 button_pos = button.GetPos();
    Dim2 button_size = button.GetSize();

    Vec2 cursor_pos;
    SDL_GetMouseState(&cursor_pos.x, &cursor_pos.y);

    if ((cursor_pos.x > button_pos.x && cursor_pos.y > button_pos.y) && (cursor_pos.x < (button_pos.x + button_size.w) && cursor_pos.y < (button_pos.y + button_size.h)))
    {
        return true;
    }

    return false;
}

void NetPong::MenuState::UpdateButtonTexture(Engine::Texture &button, Vec2 pos, int font_size, Uint8 alpha)
{
    button.ChangeFontSize(font_size);
    button.ReloadTexture(m_renderer);

    Vec2 new_pos = {pos.x - (button.GetSize().w / 2), pos.y - (button.GetSize().h / 2)};

    button.SetPosition(new_pos.x, new_pos.y);

    button.SetAlpha(alpha);
}