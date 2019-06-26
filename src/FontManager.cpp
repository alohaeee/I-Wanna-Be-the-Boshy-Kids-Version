#include "FontManager.h"

TTF_Font* FontManager::LoadFont(const char* path , int size)
{
    TTF_Font *tmpFont = TTF_OpenFont(path,size);
    return tmpFont;
}

void FontManager::Draw(TTF_Font* font, SDL_Rect src, SDL_Rect dst, const char* text, SDL_Color color)
{
    SDL_Surface *tmpSurf = TTF_RenderText_Solid(font,text,color);
    SDL_Texture *tmptext = SDL_CreateTextureFromSurface(Game::renderer, tmpSurf);
    SDL_RenderCopy(Game::renderer, tmptext, &src,&dst);
    SDL_FreeSurface(tmpSurf);
    SDL_DestroyTexture(tmptext);
}

