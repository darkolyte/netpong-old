#include <string>

#include "Audio.h"

Engine::SDL_Audio::SDL_Audio(std::string path)
{
    if (SDL_LoadWAV(path.c_str(), &m_audio_spec, &m_audio_buffer, &m_audio_duration) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load Audio with SDL Error: %s", SDL_GetError());
    }
}

Engine::SDL_Audio::~SDL_Audio()
{
    SDL_free(m_audio_buffer);
    SDL_DestroyAudioStream(m_stream);

    SDL_CloseAudioDevice(m_device);
}

void Engine::SDL_Audio::Play()
{
    if (m_audio_buffer && m_audio_duration)
    {
        SDL_ClearAudioStream(m_stream);
        SDL_PutAudioStreamData(m_stream, m_audio_buffer, m_audio_duration);
    }

    SDL_FlushAudioStream(m_stream);
}

void Engine::SDL_Audio::Pause()
{
    if (SDL_IsAudioDevicePaused(m_device))
    {
        return;
    }

    SDL_PauseAudioDevice(m_device);
}

void Engine::SDL_Audio::Resume()
{
    if (SDL_IsAudioDevicePaused(m_device))
    {
        SDL_PauseAudioDevice(m_device);
    }

    return;
}

void Engine::SDL_Audio::Stop()
{
    SDL_ClearAudioStream(m_stream);
}

bool Engine::SDL_Audio::IsPlaying() const
{
    if (SDL_GetAudioStreamAvailable(m_stream) && !SDL_IsAudioDevicePaused(m_device))
    {
        return true;
    }
    return false;
}

void Engine::SDL_Audio::SetupDevice()
{
    m_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &m_audio_spec);

    m_stream = SDL_CreateAudioStream(&m_audio_spec, &m_audio_spec);

    SDL_BindAudioStream(m_device, m_stream);
}