#pragma once
#include "Components.h"


class MainAction : public Component
{
private:
    Entity& String;
    TransformComponent *transformPlayer;
    TransformComponent *transformString;


    SpriteComponent *spritePlayer;
    SpriteComponent *spriteString; 

    KeyboardComponent *keyboardPlayer;

public:
    MainAction() = delete;
    MainAction(Entity& String) : String(String) {};

    void init() override
    {
        transformPlayer = &entity->getComponent<TransformComponent>();
        spritePlayer = &entity->getComponent<SpriteComponent>();
        keyboardPlayer = &entity->getComponent<KeyboardComponent>();

        transformString = &String.getComponent<TransformComponent>();
        spriteString = &String.getComponent<SpriteComponent>();
        spriteString->spriteFlip=SDL_FLIP_VERTICAL;
        transformString->position.y=0;
    }

    void update() override
    {
        transformString->position.x = transformPlayer->position.x;
        spriteString->spriteFlip = static_cast<SDL_RendererFlip>(spritePlayer->spriteFlip|SDL_FLIP_VERTICAL);
        if(keyboardPlayer->isActionTime)
        {
            if(transformString->position.y==0){ 
                transformString->position.y=transformPlayer->position.y*1.35;
                transformString->height = transformPlayer->height*transformPlayer->scale/3;
            }
            if(transformString->height <= transformPlayer->height*transformPlayer->scale/4)
            {
                transformString->position.y=0;
                transformString->height = 0;
                keyboardPlayer->isActionTime=false;
                keyboardPlayer->first=true;
                spritePlayer->Play("Idle");
            }
                            
            if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_UP:
                        transformString->height--;
                        break;
                    case SDLK_DOWN:
                        transformString->height++;
                        break;
                }
            }
            if(Game::event.type == SDL_KEYUP)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_UP:
                    
                        break;
                    case SDLK_DOWN:
                        break;
                }
            }
        }

    }


};