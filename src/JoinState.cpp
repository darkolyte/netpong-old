#include "JoinState.h"
#include "ExampleState.h"

NetPong::JoinState::JoinState(SDL_Renderer *&renderer, Engine::StateManager &state_stack)
    : m_renderer(renderer), m_state_stack(&state_stack) {}

NetPong::JoinState::JoinState(SDL_Renderer *&renderer, Engine::StateManager *&state_stack)
    : m_renderer(renderer), m_state_stack(state_stack) {}

void NetPong::JoinState::Init()
{
    SDL_StartTextInput();

    m_input = " ";

    m_heading_text.LoadText(m_renderer, "Enter IP Address:", {255, 255, 255, 255}, 64);
    m_heading_text.SetPosition(900 / 2 - (m_heading_text.GetSize().w / 2), 900 / 8);

    m_input_text.LoadText(m_renderer, m_input.c_str(), {255, 255, 255, 255}, 50, Engine::Texture::TTF_RENDER_BLENDED_WRAPPED);
    m_input_text.SetPosition(900 / 2 - (m_input_text.GetSize().w / 2), 900 / 4);
}

void NetPong::JoinState::Update()
{
    m_render_required = false;

    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            while (m_state_stack->GetCurrentState())
            {
                m_state_stack->PopCurrentState();
            }
        }
        else if (e.type == SDL_EVENT_KEY_DOWN)
        {
            if (e.key.keysym.sym == SDLK_BACKSPACE && m_input.length() > 0)
            {
                if (SDL_GetModState() & SDL_KMOD_SHIFT)
                {
                    m_input = " ";
                }
                else
                {
                    m_input.pop_back();
                }
                m_render_required = true;
            }
            else if (m_input.length() > 254)
            {
                break;
            }
            else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & SDL_KMOD_CTRL)
            {
                SDL_SetClipboardText(m_input.c_str());
            }
            else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & SDL_KMOD_CTRL)
            {
                if ((m_input + SDL_GetClipboardText()).length() > 254)
                    m_input += SDL_GetClipboardText();
                m_render_required = true;
            }
        }
        else if (e.type == SDL_EVENT_TEXT_INPUT)
        {
            if (m_input.length() > 254)
            {
                break;
            }

            char fchar = tolower(e.text.text[0]);

            if (!(SDL_GetModState() & SDL_KMOD_CTRL && (fchar == 'c' || fchar == 'v')))
            {
                m_input += e.text.text;
                m_render_required = true;
            }
        }
        else if (e.type == SDL_EVENT_KEY_UP && e.key.keysym.sym == SDLK_RETURN)
        {
            std::shared_ptr<Engine::State> next_state = std::make_shared<NetPong::ExampleState>(m_renderer);
            m_state_stack->PushNewState(next_state);
            return;
        }
    }

    if (m_render_required)
    {
        if (m_input == "")
        {
            m_input = " ";
        }
        m_input_text.LoadText(m_renderer, m_input.c_str(), {255, 255, 255, 255}, 50, Engine::Texture::TTF_RENDER_BLENDED_WRAPPED);
        m_input_text.SetPosition(900 / 2 - (m_input_text.GetSize().w / 2), 900 / 4);
    }

    return;
}

void NetPong::JoinState::Render()
{
    m_heading_text.Render(m_renderer);
    m_input_text.Render(m_renderer);
}

void NetPong::JoinState::Delete()
{
    return;
}