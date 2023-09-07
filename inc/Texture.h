#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

namespace Engine
{
    class Texture
    {
    public:
        Texture() : m_texture(nullptr), m_font(nullptr), m_width(0), m_height(0) {}
        ~Texture() { Texture::FreeAllResources(); }

        bool LoadImage(SDL_Renderer *&renderer, std::string path);

        bool LoadText(SDL_Renderer *&renderer, std::string text, SDL_Color text_colour);

        // void SetColor(Uint8 red, Uint8 green, Uint16 blue);

        // void SetAlpha(Uint8 alpha);

        bool SetFont(std::string path, int font_size);

        void ChangeFontSize(int size);

        // void SetBlendMode(SDL_BlendMode mode);

        void Render(float x, float y, SDL_Renderer *&renderer, SDL_FRect *clip_rect = nullptr, double angle = 0.0, SDL_FPoint *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int GetWidth() { return m_width; }
        int GetHeight() { return m_height; }

    private:
        void FreeAllResources();
        void DestroyTexture();
        void CloseFont();

    private:
        SDL_Texture *m_texture;
        TTF_Font *m_font;

        float m_width;
        float m_height;
    };
}