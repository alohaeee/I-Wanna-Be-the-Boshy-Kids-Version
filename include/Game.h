#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <vector>
#include "MyException.h"
#include "ScoreClass.h"



class Game
{
public:
    static SDL_Window *window;
    Game();
    ~Game();
    void init(const char* title, int w, int h, bool fullscreen);
   
    void handleEvent();
    void update();
    void render();
    
    void destroy();
    bool running() const;

    static bool isRunning;
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static ScoreClass score_table;
};

