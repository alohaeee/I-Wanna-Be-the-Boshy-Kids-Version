#pragma once
#include <SDL2/SDL.h>
#include "ECS/ECS.h"
#include "ECS/ColliderComponent.h"


namespace Collision
{
    namespace Rect
    {
        bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
        bool LRC(const SDL_Rect& rectA, const SDL_Rect& rectB);
    };
    bool AABB(const ColliderComponent& ColliderA, const ColliderComponent& ColliderB);
    bool LRC(const ColliderComponent& ColliderA, const ColliderComponent& ColliderB);
    bool reAABB(const ColliderComponent& ColliderA, const ColliderComponent& ColliderB);
};


namespace ColHandler
{
    void Empty(Entity& Left, Entity& Right);
    void LeftVelocityZero(Entity& Left, Entity& Right);
    void ReRandPosFishies(Entity& Left, Entity& Right);
    void ChainFishPosition(Entity& Left, Entity& Right);
}