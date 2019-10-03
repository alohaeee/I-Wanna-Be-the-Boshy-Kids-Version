#pragma once
#include "ECS/ECS.h"
#include "ECS/SpriteComponent.h"
#include "ECS/TransformComponent.h"
#include "ECS/AppleComponent.h"
#include "Game.h"
#include <random>


class SpawnComponent : public Component
{
private:
    TransformComponent *transform;
    SpriteComponent *sprite;
    AppleComponent *apple;
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
        apple = &entity->getComponent<AppleComponent>();

        left = 0;
        right = w;
    }
    void RandPos()
    {
        transform->position.y = 0;
        std::uniform_int_distribution<int> uid_pos(left,right);
        transform->position.x = static_cast<int>(uid_pos(gen));

        std::uniform_int_distribution<> uid_speed(1,4);
        transform->speed = uid_speed(gen);

        std::uniform_int_distribution<> uid_type_side(0,1);
        auto type = uid_type_side(gen);
        transform->velocity.y = 1;
            if(uid_type_side(gen))
            {
                sprite->Play("Good_Apple");
                apple->SetPoint(5);
            }
            else
            {
                sprite->Play("Bad_Apple");
                apple->SetPoint(-10);
            }

    }
};