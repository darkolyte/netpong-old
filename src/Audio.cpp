#include <string>

#include "Audio.h"

Engine::Audio::Audio(std::string path)
{
    if (SDL_LoadWAV(path.c_str(), &m_audio_spec, &m_audio_buffer, &m_audio_duration) == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load Audio with SDL Error: %s", SDL_GetError());
    }
}

Engine::Audio::~Audio()
{
    SDL_free(m_audio_buffer);
    SDL_CloseAudioDevice(m_device);
}

void Engine::Audio::Play()
{
    m_stream = SDL_CreateAudioStream(&m_audio_spec, &m_audio_spec);

    if (m_audio_buffer && m_audio_duration)
    {
        SDL_PutAudioStreamData(m_stream, m_audio_buffer, m_audio_duration);
    }

    SDL_BindAudioStream(m_device, m_stream);

    SDL_FlushAudioStream(m_stream);
}

void Engine::Audio::SetupDevice()
{
    m_device = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, &m_audio_spec);
}