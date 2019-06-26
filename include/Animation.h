#pragma once
#include <functional>
#include <SDL2/SDL.h>
using ANIM_FUNC = std::function<void(SDL_Rect&, int, int)>;
struct Animation
{
    int index;
    int frames;
    int speed;
    ANIM_FUNC animFunc;

    Animation() = default;
    Animation(int i, int f, int s, ANIM_FUNC animFunc) : index(i), frames(f), speed(s), animFunc(animFunc) {}
};

namespace AnimationFunctions
{
    void TicksMultiplyAnimation(SDL_Rect &src, int frames, int speed);
    void CarriageAnimation(SDL_Rect &src, int frames, int speed);
    void PlusAnimation(SDL_Rect &src, int frames, int speed);
};