#include "Collision.h"




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
void ColHandler::Empty(Entity& Left, Entity& Right)
{
    return;
}

void ColHandler::LeftVelocityZero(Entity& Left, Entity& Right)
{
    Left.getComponent<TransformComponent>().unUpdate();
}

void ColHandler::ReRandPosFishies(Entity& Left, Entity& Right)
{
    Left.getComponent<SpawnComponent>().RandPos();
}

