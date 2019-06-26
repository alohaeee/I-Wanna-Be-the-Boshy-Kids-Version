#pragma once

#include "Game.h"

struct TextureManager
{
    static SDL_Texture* LoadTexture(const char * path);
    static void SetToAlpha(SDL_Texture*tex, Uint8 alpha);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip);
};