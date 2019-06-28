#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "LabelInterface.h"
#include "SpriteComponent.h"
#include "Scene/SceneManager.h"




class SubMenuController : public Component
{
private:
    TransformComponent* transformCursor;
    SpriteComponent* spriteCursor;
    LabelID Begin, End;
    LabelID Cur;
    SDL_Rect Pos;
    bool isPressed=false;

public:
    SubMenuController() = delete;
    explicit SubMenuController(size_t beg, size_t end) : Begin(beg), End(end), Cur(Begin){
        Pos = LabelInterface::LabelsVector[1][Cur]->GetPos();
    }
    void init() override
    {
        transformCursor = &entity->getComponent<TransformComponent>();
        spriteCursor = &entity->getComponent<SpriteComponent>();
        transformCursor->position.x = Pos.x + Pos.w;
        transformCursor->position.y = Pos.y;
    }
    void update() override
    {
        Pos = LabelInterface::LabelsVector[1][Cur]->GetPos();
        transformCursor->position.x = Pos.x + Pos.w;
        transformCursor->position.y = Pos.y;
        if(Game::event.type == SDL_KEYDOWN)
        {
            if(!isPressed)
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
                                entity->manager.unFreezeALL();
                                entity->Hold();
                                LabelInterface::KillGroup(1);
                                break;
                            case 1:
                                entity->sceneManager.changeActiveScene(0);
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
    }
};