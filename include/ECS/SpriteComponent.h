#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "../TextureManager.h"
#include "../Animation.h"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <iostream>
#include <functional>



class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;  
    
    
    ANIM_FUNC curFunc;
    bool animated = false;
    int speed = 100;
public:

    int animIndex = 0;
    int frames;


    SDL_Rect srcRect, dstRect; 
    std::string 
    curAnim;
    std::map<std::string, std::unique_ptr<Animation>> animations;
    
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;
    SpriteComponent(const char *path)
    {
        setTex(path);
    };
    SpriteComponent(const char *path, bool isAnimated) : animated(isAnimated)
    {
        setTex(path);
    };
    ~SpriteComponent()
    {
        if(texture) SDL_DestroyTexture(texture);
    }

    void setAnim(std::string animName,int index,int frames, int speed)
    {   
        std::unique_ptr<Animation> uPtr { new Animation(index,frames,speed, AnimationFunctions::TicksMultiplyAnimation)};
        animations.emplace(animName, std::move(uPtr));
    }
    void setAnim(std::string animName,int index,int frames, int speed, ANIM_FUNC anim_func)
    {
        std::unique_ptr<Animation> uPtr { new Animation(index,frames,speed, anim_func)};
        animations.emplace(animName, std::move(uPtr));
    }

    void setAlpha(int alpha)
    {
        TextureManager::SetToAlpha(texture, alpha);
    }
    void setTex(const char *path)
    {
        texture = TextureManager::LoadTexture(path);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override
    {
        if(animated)
        {
            srcRect.y = animIndex * transform->height;
            curFunc(srcRect, frames, speed);
        }
        srcRect.w = transform->width;
        srcRect.h = transform->height;
        
        dstRect.x = static_cast<int>(transform->position.x);
        dstRect.y = static_cast<int>(transform->position.y);

        dstRect.w = transform->width * transform->scale;
        dstRect.h = transform->height * transform->scale;
    }

    void draw() override
    { 
        
        TextureManager::Draw(texture,srcRect,dstRect,spriteFlip);
    }

    void Play(std::string animName)
    {
        auto anim = animations.at(animName).get();
        frames = anim->frames;
        animIndex = anim->index;
        speed = anim->speed;
        curFunc = anim->animFunc;
        curAnim = animName;
    }


};