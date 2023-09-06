#pragma once

#include <SDL3/SDL.h>

#include <string>

namespace Engine
{
    // Interface for Audio
    class IAudio
    {
    public:
        virtual ~IAudio() {} // Virtual destructor, ie. cannot instantiate interface

        virtual void Play() = 0;
        // virtual void Pause() = 0;
        // virtual void Resume() = 0;
        // virtual void Stop() = 0;
        // virtual bool GetPlaybackStatus() = 0;

        // virtual bool ToggleLoop() = 0;
        // virtual bool GetLoopStatus() = 0;
    };

    class Audio : public IAudio
    {
    public:
        Audio(std::string path);
        ~Audio();

        void Play() override;
        // void Pause() override;
        // void Resume() override;
        // void Stop() override;
        // bool GetPlaybackStatus() override;

        void SetupDevice();

    private:
        SDL_AudioDeviceID m_device;
        SDL_AudioStream *m_stream;

        SDL_AudioSpec m_audio_spec;
        Uint8 *m_audio_buffer;
        Uint32 m_audio_duration;
    };
}