#pragma once
#include "ECS/ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "KeyboardComponent.h"
#include "ColliderComponent.h"
#include "SpawnComponent.h"
#include "ScoreComponent.h"


class MainAction : public Component
{
private:
   
    TransformComponent *transformString;
    SpriteComponent *spriteString;
    ColliderComponent *colliderString; 
    ScoreComponent *scoreString;
    
    
    Entity& Player;
    TransformComponent *transformPlayer;
    SpriteComponent *spritePlayer;
    KeyboardComponent *keyboardPlayer;




    

  
public:
    Entity* CurFish;
    TransformComponent *transformFish;
    SpriteComponent *spriteFish;

    bool Catched = false;

    MainAction() = delete;
    MainAction(Entity& Player) : Player(Player) {};

    void init() override
    {
        transformPlayer = &Player.getComponent<TransformComponent>();
        spritePlayer = &Player.getComponent<SpriteComponent>();
        keyboardPlayer = &Player.getComponent<KeyboardComponent>();

        transformString = &entity->getComponent<TransformComponent>();
        spriteString = &entity->getComponent<SpriteComponent>();
        colliderString =&entity->getComponent<ColliderComponent>();
        scoreString =&entity->getComponent<ScoreComponent>();
        spriteString->spriteFlip=SDL_FLIP_VERTICAL;
        transformString->position.y=0;
    }

    void update() override
    {
        transformString->position.x = transformPlayer->position.x;
        spriteString->spriteFlip = static_cast<SDL_RendererFlip>(spritePlayer->spriteFlip|SDL_FLIP_VERTICAL);
        
        //String_Position Routine
        if(keyboardPlayer->isActionTime)
        {
            //spawnString
            if(transformString->position.y==0){ 
                transformString->position.y=transformPlayer->position.y*1.35;
                transformString->height = transformPlayer->height*transformPlayer->scale/3;
            }
            //End action
            if(transformString->height <= transformPlayer->height*transformPlayer->scale/4)
            {
                transformString->position.y=0;
                transformString->height = 0;
                keyboardPlayer->isActionTime=false;
                keyboardPlayer->first=true;
                spritePlayer->Play("Idle");
                if(spriteFish->curAnim == "Catched_Emerald")
                    scoreString->PlusScore(5);
                else if(spriteFish->curAnim == "Catched_Purple")
                    scoreString->PlusScore(10);
                Catched = false;
                CurFish->getComponent<SpawnComponent>().RandPos();
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

            if(Catched)
            {
                transformFish->position.x = colliderString->collider.x-(colliderString->collider.w-10)*transformString->scale;
                transformFish->position.y = colliderString->collider.y;
            }
        }

    }


};