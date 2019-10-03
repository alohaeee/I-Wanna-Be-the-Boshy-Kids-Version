#include "Game.h"
#include "ECS/Components.h"
#include "TextureManager.h"
#include "Collision.h"
#include "Vector2D.h"

#include "Scene/SceneHeader.h"

SceneManager sceneManager;

//Entity manager
Manager *manager = new Manager(sceneManager);

//static member init
SDL_Window *Game::window = nullptr;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
ScoreClass Game::score_table("inf/score_table.txt");
bool Game::isRunning = true;




Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int w, int h, bool fullscreen)
{
    isRunning = true;
    try
    {
        if(SDL_Init(SDL_INIT_EVERYTHING) == -1) throw MyException(SDL_GetError(), -1);
        else std::cout << "SDL initialize succesfully!" << std::endl;

        if(IMG_Init(IMG_INIT_PNG) == 0) throw MyException(IMG_GetError(), -1);
        else std::cout << "IMG initialize succesfully!" << std::endl;

        if(TTF_Init() == -1) throw MyException(TTF_GetError(), -1);
        else std::cout << "TTF initialize succesfully!" << std::endl;



        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 
            fullscreen == true ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN);
        if(window==nullptr) throw MyException(SDL_GetError(), -22);
        else std::cout << "Window created!" << std::endl;

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer==nullptr) throw MyException(SDL_GetError(), -22);
        else
        {
            std::cout << "Renderer created!" << std::endl;
            if(SDL_SetRenderDrawColor(renderer,255,255,255,255) == -1) throw MyException(SDL_GetError(), -22);
            else std::cout << "Render color was set!" << std::endl;
            //SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        } 
        if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) throw MyException(Mix_GetError(), -22);
        else
        {
            std::cout << "Mixer initialize succesfully!" << std::endl;
        }
        

        SDL_Surface *icon = IMG_Load("ss22.png");
        if(icon == nullptr) throw MyException(IMG_GetError(), -33);
        else std::cout << "Icon was set!" << std::endl;
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);

        
        sceneManager.addScene<Scene_Menu>(manager);
        sceneManager.addScene<Scene_Game>(manager);
        sceneManager.changeActiveScene(0);
       

    } 
    catch(MyException &e)
    {
        throw e;
    }
}

void Game::handleEvent()
{
    SDL_PollEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        default:
            break;
        
    } 
    sceneManager.event();
}


void Game::update()
{
    sceneManager.update();
}




void Game::render()
{
    SDL_RenderClear(renderer);

    sceneManager.render();
   
    SDL_RenderPresent(renderer);
}

void Game::destroy()
{
    score_table.distruct();
    delete manager;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
    
}

bool Game::running() const
{
    return isRunning;
}

