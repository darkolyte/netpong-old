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

    m_size.w = image_surface->w;
    m_size.h = image_surface->h;

    SDL_DestroySurface(image_surface);

    return true;
}

bool Engine::Texture::SetFont(std::string path, int font_size)
{
    CloseFont();

    m_font = TTF_OpenFont(path.c_str(), font_size);

    if (!m_font)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font at %s with error %s", path.c_str(), TTF_GetError());
        return false;
    }
    return true;
}

void Engine::Texture::ChangeFontSize(int size)
{
    if (m_font)
    {
        TTF_SetFontSize(m_font, size);
    }
}

bool Engine::Texture::LoadText(SDL_Renderer *&renderer, std::string text, SDL_Color text_colour, int font_size)
{
    DestroyTexture();

    if (!m_font)
    {
        SetFont("res/Font/Roboto-Regular.ttf", font_size);
    }

    m_text = text;
    m_text_colour = text_colour;

    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(m_font, m_text.c_str(), m_text_colour);

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

    m_size.w = text_surface->w;
    m_size.h = text_surface->h;

    SDL_DestroySurface(text_surface);

    return true;
}

bool Engine::Texture::ReloadTexture(SDL_Renderer *&renderer)
{
    if (!m_texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "No texture loaded yet!");
        return false;
    }
    DestroyTexture();

    SDL_Surface *text_surface = TTF_RenderUTF8_Blended(m_font, m_text.c_str(), m_text_colour);

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

    m_size.w = text_surface->w;
    m_size.h = text_surface->h;

    SDL_DestroySurface(text_surface);

    return true;
}

void Engine::Texture::SetPosition(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void Engine::Texture::Render(SDL_Renderer *&renderer, float x, float y, SDL_FRect *clip_rect, double angle, SDL_FPoint *center, SDL_RendererFlip flip)
{

    m_pos.x = x ? x : m_pos.x;
    m_pos.y = y ? x : m_pos.y;

    SDL_FRect render_rect = {m_pos.x, m_pos.y, m_size.w, m_size.h};

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

        m_size.w = 0;
        m_size.h = 0;
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

void Engine::Texture::SetColor(Uint8 red, Uint8 green, Uint16 blue)
{
    SDL_SetTextureColorMod(m_texture, red, green, blue);
}

void Engine::Texture::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(m_texture, alpha);
}