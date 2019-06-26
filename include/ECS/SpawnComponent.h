#pragma once
#include "ECS/ECS.h"
#include "ECS/SpriteComponent.h"
#include "ECS/TransformComponent.h"
#include "Game.h"
#include <random>


class SpawnComponent : public Component
{
private:
    TransformComponent *transform;
    SpriteComponent *sprite;
    std::random_device rd;
    std::mt19937 gen;
    int left = 300;
    int right = 536;
    int w, h;
public:
    SpawnComponent(){
        gen.seed(rd());
        SDL_GetWindowSize(Game::window, &w,&h);
    };
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        left = h/2;
        right = h - transform->height;
    }
    void RandPos()
    {
        std::uniform_int_distribution<int> uid_pos(left,right);
        transform->position.y = static_cast<int>(uid_pos(gen));

        std::uniform_int_distribution<> uid_speed(1,4);
        transform->speed = uid_speed(gen);

        std::uniform_int_distribution<> uid_type_side(0,1);
        auto type = uid_type_side(gen);
        if(type)
        {
            auto side = uid_type_side(gen);
            if(side)
            {
                transform->position.x = w;
                transform->velocity.x = -1;
                sprite->spriteFlip = SDL_FLIP_NONE;
            }
            else 
            {
                transform->position.x = 0.0f-transform->scale*transform->width;
                transform->velocity.x = 1;
                sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            }
            if(uid_type_side(gen))
            {
                sprite->Play("Idle_Purple");
            }
            else
            {
                sprite->Play("Idle_Emerald");
            }
        }
        else
        {
            transform->position.x = w;
            transform->velocity.x = -1;
            sprite->spriteFlip = SDL_FLIP_NONE;
            sprite->Play("Idle_Rubbish");
        }
    }

};