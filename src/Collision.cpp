#include "Collision.h"

#include "ECS/Components.h"


bool Collision::Rect::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if (
        rectA.x + rectA.w >= rectB.x &&
        rectB.x + rectB.w >= rectA.x &&
        rectA.y + rectA.h >= rectB.y &&
        rectB.y + rectB.h >= rectA.y
        )
    {
        return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent& ColliderA, const ColliderComponent& ColliderB)
{
    if(Collision::Rect::AABB(ColliderA.collider, ColliderB.collider))
    {
        std::cout << ColliderA.tag << " hit:" << ColliderB.tag << std::endl;
        return true;
    }
    return false;
}

bool Collision::reAABB(const ColliderComponent& ColliderA, const ColliderComponent& ColliderB)
{
    if(Collision::Rect::AABB(ColliderA.collider, ColliderB.collider))
    {
        return false;
    }
    std::cout << ColliderA.tag << " hit:" << ColliderB.tag << std::endl;
    return true;
}


bool Collision::Rect::LRC(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
    if(rectA.x<=rectB.x || rectA.x+rectA.w>=rectB.x+rectB.w)
        return true;
    return false;
}

bool Collision::LRC(const ColliderComponent& ColliderA, const ColliderComponent& ColliderB)
{
    if(Collision::Rect::LRC(ColliderA.collider, ColliderB.collider))
    {
        std::cout << ColliderA.tag << " hit:" << ColliderB.tag << std::endl;
        return true;
    }
    return false;
}

//using namespace ColHandler;
void ColHandler::Empty(Entity& , Entity& )
{
    return;
}

void ColHandler::LeftVelocityZero(Entity& Left, Entity& )
{
    Left.getComponent<TransformComponent>().unUpdate();
}

void ColHandler::ReRandPosFishies(Entity& Left, Entity& )
{
    Left.getComponent<SpawnComponent>().RandPos();
}


void ColHandler::ChainFishPosition(Entity& Left, Entity& Right)
{
    auto actionComponent = &Right.getComponent<MainAction>();
    if(!actionComponent->Catched)
    {
        Left.getComponent<TransformComponent>().velocity.x = 0;
        actionComponent->Catched = true;
        auto sprite = &Left.getComponent<SpriteComponent>();
        actionComponent->CurFish = &Left;
        actionComponent->spriteFish = sprite;
        actionComponent->transformFish = &Left.getComponent<TransformComponent>();
        std::string CurAnimation = sprite->curAnim;
        if(CurAnimation == "Idle_Purple")
            sprite->Play("Catched_Purple");
        else if (CurAnimation == "Idle_Emerald")
            sprite->Play("Catched_Emerald");
        else if(CurAnimation == "Idle_Rubbish")
            sprite->Play("Catched_Rubbish");
    }
}

