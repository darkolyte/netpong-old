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
    m_join_button.SetPosition(900 / 2 - (m_join_button.GetSize().w / 2), 400 - (m_join_button.GetSize().h / 2));

    m_exit_button.LoadText(m_renderer, "Exit", {255, 255, 255, 255}, 52);
    m_exit_button.SetPosition(900 / 2 - (m_exit_button.GetSize().w / 2), 550 - (m_exit_button.GetSize().h / 2));
}

void NetPong::MenuState::Update()
{
    if (CursorOverButton(m_join_button))
    {
        if (!m_was_over_join)
        {
            UpdateButtonTexture(m_join_button, {900 / 2, 400}, 56);
            m_was_over_join = true;
        }
    }
    else
    {
        if (m_was_over_join)
        {
            UpdateButtonTexture(m_join_button, {900 / 2, 400}, 52);
            m_was_over_join = false;
        }
    }

    if (CursorOverButton(m_exit_button))
    {
        if (!m_was_over_exit)
        {
            UpdateButtonTexture(m_exit_button, {900 / 2, 550}, 56);
            m_was_over_exit = true;
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

void NetPong::MenuState::UpdateButtonTexture(Engine::Texture &button, Vec2 pos, int font_size)
{
    button.ChangeFontSize(font_size);

    Vec2 new_pos = {pos.x - (button.GetSize().w / 2), pos.y - (button.GetSize().h / 2)};

    button.SetPosition(new_pos.x, new_pos.y);
    button.ReloadTexture(m_renderer);
}