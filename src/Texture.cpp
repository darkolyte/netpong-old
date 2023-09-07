#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Texture.h"

bool Engine::Texture::LoadImage(SDL_Renderer *&renderer, std::string path)
{
    DestroyTexture();

    SDL_Surface *image_surface = IMG_Load(path.c_str());

    if (!image_surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load image at %s, with error %s", path.c_str(), IMG_GetError());
        return false;
    }

    SDL_SetSurfaceColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 0xFF, 0xFF, 0xFF));

    m_texture = SDL_CreateTextureFromSurface(renderer, image_surface);

    if (!m_texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create texture from %s, with error %s", path.c_str(), IMG_GetError());
        return false;
    }

    m_width = image_surface->w;
    m_height = image_surface->h;

    SDL_DestroySurface(image_surface);

    return true;
}

bool Engine::Texture::SetFont(std::string path, int font_size)
{
    CloseFont();

    m_font = TTF_OpenFont(path.c_str(), font_size);

    if (m_font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font at %s with error %s", path.c_str(), TTF_GetError());
        return true;
    }
    return false;
}

void Engine::Texture::ChangeFontSize(int size)
{
    if (m_font)
    {
        TTF_SetFontSize(m_font, size);
    }
}

bool Engine::Texture::LoadText(SDL_Renderer *&renderer, std::string text, SDL_Color text_colour)
{
    DestroyTexture();

    if (!m_font)
    {
        SetFont("res/Font/Roboto-Regular.ttf", 48);
    }

    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(m_font, text.c_str(), text_colour);

    if (!text_surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to render text surface with error %s", TTF_GetError());
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

    if (!m_texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create texture with error %s", IMG_GetError());
        return false;
    }

    m_width = text_surface->w;
    m_height = text_surface->h;

    SDL_DestroySurface(text_surface);

    return true;
}

void Engine::Texture::Render(float x, float y, SDL_Renderer *&renderer, SDL_FRect *clip_rect, double angle, SDL_FPoint *center, SDL_RendererFlip flip)
{
    SDL_FRect render_rect = {x, y, m_width, m_height};

    if (clip_rect)
    {
        render_rect.w = clip_rect->w;
        render_rect.h = clip_rect->h;
    }

    SDL_RenderTextureRotated(renderer, m_texture, clip_rect, &render_rect, angle, center, flip);
}

void Engine::Texture::FreeAllResources()
{
    DestroyTexture();
    CloseFont();
}

void Engine::Texture::DestroyTexture()
{
    if (m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;

        m_width = 0;
        m_height = 0;
    }
}

void Engine::Texture::CloseFont()
{
    if (m_font)
    {
        TTF_CloseFont(m_font);
        m_font = nullptr;
    }
}