#include "TextureManager.h"
#include <iostream>
SDL_Texture* TextureManager::LoadTexture(const char* path)
{
    SDL_Surface *tempSurface= IMG_Load(path);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer,tempSurface);
    if(tex == NULL) std::cout << "AAA BLYAT" << std::endl;
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::SetToAlpha(SDL_Texture* tex, Uint8 alpha)
{
    if(SDL_SetTextureAlphaMod(tex,alpha) == -1) std::cout << SDL_GetError() << std::endl;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer,tex,&src,&dst, NULL, NULL, flip);
}