#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "LabelInterface.h"
#include "SpriteComponent.h"
#include "PlayerNameEvent.h"
#include "AudioComponent.h"
#include "../Game.h"



class MenuController : public Component
{
private:
    TransformComponent* transformCursor;
    SpriteComponent* spriteCursor;
    PlayerNameEvent* nameEventCursor;
    AudioComponent* audioCursor;
    LabelID Begin, End;
    LabelID Cur;
    SDL_Rect Pos;
    bool isPressed=false;

    bool isFullscreen = false;
    bool flag=false;


public:
    explicit MenuController(size_t beg, size_t end): Begin(beg), End(end), Cur(Begin){
        Pos = LabelInterface::LabelsVector[0][Cur]->GetPos();
    }
    void init() override
    {
        transformCursor = &entity->getComponent<TransformComponent>();
        spriteCursor = &entity->getComponent<SpriteComponent>();
        nameEventCursor = &entity->getComponent<PlayerNameEvent>();
        audioCursor = &entity->getComponent<AudioComponent>();
        transformCursor->position.x = Pos.x + Pos.w;
        transformCursor->position.y = Pos.y;
    }
    void update() override
    {
        Pos = LabelInterface::LabelsVector[0][Cur]->GetPos();
        transformCursor->position.x = Pos.x + Pos.w;
        transformCursor->position.y = Pos.y;
        if(Game::event.type == SDL_KEYDOWN)
        {
            audioCursor->Play();
            if(!isPressed&&flag)
            {
                switch(Game::event.key.keysym.sym)
                {
                
                    case SDLK_UP:
                        if(Cur > Begin)
                        {
                            isPressed = true;
                            Cur--;
                        }
                        break;
                    case SDLK_DOWN:
                        if(Cur<End)
                        {
                            
                            isPressed = true;
                            Cur++;
                        }
                        break;
                    case SDLK_RETURN:
                        switch(Cur)
                        {
                            case 0:
                                LabelInterface::MakeActiveGroup(2);
                                LabelInterface::KillGroup(0);
                                this->freeze = true;
                                nameEventCursor->freeze=false;
                                break;
                            case 1:
                                LabelInterface::KillGroup(0);
                                entity->Hold();
                                LabelInterface::MakeActiveGroup(3);
                                


                                break;
                            case 2:
                                if(!isFullscreen)
                                {
                                    SDL_SetWindowFullscreen(Game::window,SDL_WINDOW_FULLSCREEN);
                                    isFullscreen = true;
                                }
                                else {
                                    SDL_SetWindowFullscreen(Game::window,0);
                                    isFullscreen=false;
                                }
                                break;
                            case 3:
                                Game::isRunning = false;
                                break;
                        }
                        isPressed=true;
                        break;
                }
            }
        }
        if(Game::event.type == SDL_KEYUP)
        {
            switch(Game::event.key.keysym.sym)
            {  
                case SDLK_UP:
                    isPressed=false;
                    break;
                case SDLK_DOWN:
                    isPressed=false;
                    break; 
                case SDLK_RETURN:
                    isPressed=false;
                    break;
                
            }
        }
        flag = true;
    }
};