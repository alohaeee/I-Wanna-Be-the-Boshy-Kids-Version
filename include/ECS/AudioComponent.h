#pragma once
#include "ECS.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

class AudioComponent : public Component 
{
private:
    Mix_Chunk *chunk = nullptr;
    int ch;
    
public:
    AudioComponent(std::string path, int channel) : ch(channel)
    {
        chunk = Mix_LoadWAV(path.c_str());
        if(chunk) std::cerr << "FINE " << std::endl;
        else std::cerr << "AAAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
        std::cerr << static_cast<int>(chunk->alen) << std::endl;
    };
    ~AudioComponent()
    {
        Mix_FreeChunk(chunk);
    };
    void init() override
    {

    }
    void update() override
    {
    }
    void Play()
    {
        if(!Mix_Playing(ch))
            if(Mix_PlayChannel(ch,chunk,0) == -1 ) std::cerr << Mix_GetError() << std::endl;
    }
    

};