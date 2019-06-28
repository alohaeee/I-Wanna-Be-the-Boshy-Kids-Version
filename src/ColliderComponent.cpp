#include "ECS/ColliderComponent.h"

std::map<std::string,ColliderComponent*> ColliderComponent::colliders;

void ColliderUpdateFunc::TransfromBasicCollider(ColliderComponent &CollComp)
{
        CollComp.collider.x = static_cast<int>(CollComp.transform->position.x);
        CollComp.collider.y = static_cast<int>(CollComp.transform->position.y);
        CollComp.collider.w = CollComp.transform->width * CollComp.transform->scale;
        CollComp.collider.h = CollComp.transform->height * CollComp.transform->scale;
}

void ColliderUpdateFunc::TransfromFISHCollider(ColliderComponent &CollComp)
{
        if(CollComp.sprite->spriteFlip == static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL))
            CollComp.collider.x = static_cast<int>(CollComp.transform->position.x)+27;
        else CollComp.collider.x = static_cast<int>(CollComp.transform->position.x);
        CollComp.collider.y = static_cast<int>(CollComp.transform->position.y)+10*CollComp.transform->scale;
        CollComp.collider.w = (CollComp.transform->width-30) * CollComp.transform->scale;
        CollComp.collider.h = (CollComp.transform->height-20) * CollComp.transform->scale;
}
void ColliderUpdateFunc::TransfromHOOKCollider(ColliderComponent &CollComp)
{
    CollComp.collider.w=CollComp.transform->scale*10;
    CollComp.collider.h=CollComp.transform->scale*10;
    if(CollComp.sprite->spriteFlip == static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL|SDL_FLIP_VERTICAL))
    {
        CollComp.collider.x=static_cast<int>(5*CollComp.transform->scale+CollComp.transform->position.x);  
    }
    else
    {
        CollComp.collider.x=static_cast<int>((CollComp.transform->width-15)*CollComp.transform->scale+CollComp.transform->position.x);   
    }
    CollComp.collider.y=static_cast<int>((CollComp.transform->height-18)*CollComp.transform->scale+CollComp.transform->position.y);
}