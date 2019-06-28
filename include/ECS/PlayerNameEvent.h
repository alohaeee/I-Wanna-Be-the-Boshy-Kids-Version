#pragma once
#include "ECS.h"
#include "SpriteComponent.h"
#include "LabelInterface.h"
#include "TransformComponent.h"
#include "Scene/SceneManager.h"
#include "Game.h"


class PlayerNameEvent : public Component
{
private:
    Entity& Player;
    SpriteComponent* spritePlayer;
    TransformComponent* transformPlayer;
    TransformComponent* transformCursor;
    LabelInterface* label;
    bool goPLAY=false;
    std::string Text;
    size_t Max=12;
    SDL_Rect Pos;
    LabelID TypedID;

    bool isPressed = false;
public:
    PlayerNameEvent(Entity &Player, LabelID id) : Player(Player), TypedID(id) {
    }

    void init() override
    {
        transformCursor = &entity->getComponent<TransformComponent>();
        transformPlayer = &Player.getComponent<TransformComponent>();
        spritePlayer=&Player.getComponent<SpriteComponent>();
        label=LabelInterface::LabelsVector[2][TypedID];
        
    }
    void update() override
    {
        if(!goPLAY)
        {
            
            if(Game::event.type == SDL_KEYDOWN)
            {
                
                if(Game::event.key.keysym.sym>= SDLK_0 && Game::event.key.keysym.sym <= SDLK_9 
                || Game::event.key.keysym.sym>= SDLK_a && Game::event.key.keysym.sym <= SDLK_z)
                {
                    if(Text.size()<=12)
                        Text.push_back(Game::event.key.keysym.sym);
                    label->ChangeText(Text);
                    label->SetText();
                }
                if(Game::event.key.keysym.sym == SDLK_BACKSPACE && !isPressed)
                {                    
                    if(Text.size()>0)
                        Text.pop_back();
                    label->ChangeText(Text);
                    label->SetText();
                    isPressed = true;
                }
                if(Game::event.key.keysym.sym == SDLK_RETURN)
                {
                    if(Text.size()>0 && Text!="\n"){
                        goPLAY=true;
                        spritePlayer->srcRect.x = 0;
                        spritePlayer->Play("Play");
                    }
                }
                Pos = label->GetPos();
                transformCursor->position.x = Pos.x + Pos.w;
                transformCursor->position.y = Pos.y;
            }
            if(Game::event.type == SDL_KEYUP)
            {
                if(Game::event.key.keysym.sym == SDLK_BACKSPACE)
                    isPressed = false;
            }
            
        }
        else
        {
            if(spritePlayer->srcRect.x < (spritePlayer->frames-1)*transformPlayer->width);
            else 
            {   
                Game::score_table.PushName(Text);
                entity->sceneManager.changeActiveScene(1);
            }
        }
        
    }
};