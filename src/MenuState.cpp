#include <SDL3/SDL.h>

#include "State.h"
#include "Audio.h"
#include "Maths.h"
#include "Texture.h"

#include "MenuState.h"

NetPong::MenuState::MenuState(SDL_Renderer *&renderer)
    : m_bgm("res/Audio/rain.wav")
{
    m_renderer = renderer;
}

void NetPong::MenuState::Init()
{
    m_bgm.SetupDevice();

    m_title_text.LoadText(m_renderer, "NetPong", {255, 255, 255, 255}, 92);
    m_title_text.SetPosition(900 / 2 - (m_title_text.GetSize().w / 2), 900 / 8);

    m_join_button.LoadText(m_renderer, "Join", {255, 255, 255, 255}, 52);
    m_join_button.SetPosition(900 / 2 - (m_join_button.GetSize().w / 2), 400);

    m_exit_button.LoadText(m_renderer, "Exit", {255, 255, 255, 255}, 52);
    m_exit_button.SetPosition(900 / 2 - (m_exit_button.GetSize().w / 2), 550);
}

void NetPong::MenuState::Update()
{
    if (m_bgm.IsPlaying())
    {
        return;
    }
    m_bgm.Play();
}

void NetPong::MenuState::Render()
{
    m_title_text.Render(m_renderer);
    m_join_button.Render(m_renderer);
    m_exit_button.Render(m_renderer);
}

void NetPong::MenuState::Delete()
{
    return;
}

bool NetPong::MenuState::CursorOverJoinButton()
{
    Vec2 pos = m_join_button.GetPos();
    Dim2 size = m_join_button.GetSize();
}