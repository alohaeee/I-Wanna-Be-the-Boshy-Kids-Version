#include "Game.h"


Game *game;


int main() 
{

    //FPS rouitine
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    //init game
    game = new Game();
    try{
    game->init("Fishing for fishies", 800, 600, false);
    
    while(game->running())
    {
        frameStart=SDL_GetTicks();

        game->handleEvent();
        game->update();
        game->render();
        
        frameTime=SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime)
        {
            SDL_Delay(frameDelay-frameTime);
        }
    }

    }catch(MyException &e)
    {
        game->destroy();
        std::cerr << e.GetError() << std::endl;
        return e.GetVal();
    };


    game->destroy();

    return 0;
}