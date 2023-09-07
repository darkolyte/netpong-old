#pragma once

#include <string>

#include <SDL3/SDL.h>

namespace Engine
{
    // Base class for audio implementations
    class Audio
    {
    public:
        virtual ~Audio() {} // Virtual destructor, ie. cannot instantiate interface

        // Member functions for an audio implementation

        virtual void Play() = 0;
        virtual void Pause() = 0;
        virtual void Resume() = 0;
        virtual void Stop() = 0;
        virtual bool IsPlaying() const = 0;

        // virtual bool ToggleLoop() = 0;
        // virtual bool GetLoopStatus() = 0;
    };

    class SDL_Audio : public Audio
    {
    public:
        SDL_Audio(std::string path);
        ~SDL_Audio();

        void Play() override;
        void Pause() override;
        void Resume() override;
        void Stop() override;
        bool IsPlaying() const override;

        void SetupDevice();

    private:
        SDL_AudioDeviceID m_device;
        SDL_AudioStream *m_stream;

        SDL_AudioSpec m_audio_spec;
        Uint8 *m_audio_buffer;
        Uint32 m_audio_duration;
    };
}