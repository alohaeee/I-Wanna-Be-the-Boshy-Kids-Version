#include "Animation.h"



void AnimationFunctions::TicksMultiplyAnimation(SDL_Rect &src, int frames, int speed)
{
    src.x=src.w*static_cast<int>((SDL_GetTicks()/speed)%frames);
}   

void AnimationFunctions::CarriageAnimation(SDL_Rect &src, int frames, int speed)
{
    src.x=static_cast<int>((SDL_GetTicks()/speed)%frames);   
}

void AnimationFunctions::PlusAnimation(SDL_Rect &src, int frames, int speed)
{
    static int prev=static_cast<int>((SDL_GetTicks()/speed)%frames);
    int cur = static_cast<int>((SDL_GetTicks()/speed)%frames);
    if(cur!=prev) {
        src.x+=src.w;
        prev = cur;
    }
}
