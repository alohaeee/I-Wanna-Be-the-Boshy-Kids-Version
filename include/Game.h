#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "MyException.h"



class Game
{
private:
    bool isRunning;
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


    static SDL_Renderer *renderer;
    static SDL_Event event;
};

