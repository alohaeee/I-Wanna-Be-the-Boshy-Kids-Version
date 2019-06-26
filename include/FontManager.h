#pragma once

#include "Game.h"


class FontManager
{
public:
    static TTF_Font* LoadFont(const char* path, int size);
    static void Draw(TTF_Font* font, SDL_Rect src, SDL_Rect dst, const char* text, SDL_Color color);
};