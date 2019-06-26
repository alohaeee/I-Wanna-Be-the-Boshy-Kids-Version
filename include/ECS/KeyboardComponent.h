#pragma once

#include "Components.h"
#include <string>

struct KeyboardComponent : public Component
{
    TransformComponent *transform;
    SpriteComponent *sprite;


    bool first=true;
    bool isActionTime=false;

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }
    void update() override
    {
        if(sprite->curAnim == "Action"){
            if(sprite->srcRect.x == sprite->srcRect.w*(sprite->frames-2))
            {
                isActionTime = true;
                sprite->Play("AfterIdle");
            } 
        }
        if(Game::event.type == SDL_KEYDOWN)
        {
            switch(Game::event.key.keysym.sym)
            {
                case SDLK_a:
                    transform->velocity.x = -1;
                    sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                    if(!isActionTime)
                        sprite->Play("Walk");
                    else 
                        sprite->Play("AfterWalk");
                    break;
                case SDLK_d:
                    transform->velocity.x = 1;
                    sprite->spriteFlip = SDL_FLIP_NONE;
                    if(!isActionTime)
                        sprite->Play("Walk");
                    else 
                        sprite->Play("AfterWalk");
                    break;
                case SDLK_SPACE:
                    
                    if(!isActionTime) {
                        if(first) {
                            sprite->srcRect.x=0;
                            first = false;
                        }
                        sprite->Play("Action");
                    }
            }
        }
        if(Game::event.type == SDL_KEYUP) 
        {
            switch(Game::event.key.keysym.sym)
            {
                case SDLK_a:
                    transform->velocity.x = 0;
                    if(!isActionTime)
                        sprite->Play("Idle");
                    else 
                        sprite->Play("AfterIdle");
                    break;
                case SDLK_d:
                    transform->velocity.x= 0;
                    if(!isActionTime)
                        sprite->Play("Idle");
                    else 
                        sprite->Play("AfterIdle");
                    break;
                case SDLK_SPACE:
                if(!isActionTime){
                    first = true;
                    sprite->Play("Idle");
                }
            }
        }
    }
    
};