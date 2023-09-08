#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Maths.h"

namespace Engine
{
    class Texture
    {
    public:
        Texture() : m_texture(nullptr), m_font(nullptr), m_size({0, 0}), m_pos({0, 0}) {}
        ~Texture() { Texture::FreeAllResources(); }

        bool LoadImage(SDL_Renderer *&renderer, std::string path);

        bool LoadText(SDL_Renderer *&renderer, std::string text, SDL_Color text_colour, int font_size = 48);

        // void SetColor(Uint8 red, Uint8 green, Uint16 blue);

        // void SetAlpha(Uint8 alpha);

        bool SetFont(std::string path, int font_size);

        void ChangeFontSize(int size);

        void SetPosition(int x, int y);

        bool ReloadTexture(SDL_Renderer *&renderer);

        // void SetBlendMode(SDL_BlendMode mode);

        void Render(SDL_Renderer *&renderer, float x = NULL, float y = NULL, SDL_FRect *clip_rect = nullptr, double angle = 0.0, SDL_FPoint *center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);

        Dim2 GetSize() { return m_size; }
        Vec2 GetPos() { return m_pos; }

    private:
        void FreeAllResources();
        void DestroyTexture();
        void CloseFont();

    private:
        SDL_Texture *m_texture;

        TTF_Font *m_font;
        SDL_Color m_text_colour;
        std::string m_text;

        Dim2 m_size;

        Vec2 m_pos;
    };
}