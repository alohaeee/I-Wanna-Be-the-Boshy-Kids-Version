#pragma once
#include "ECS.h"
#include <SDL2/SDL.h>
#include "LabelInterface.h"


class TimerComponent : public Component
{
private:
    Uint32 mStartTicks;
    Uint32 mPausedTicks;
    int curTimeSecond;
    LabelInterface* LI;
    int lastTime=0;

    int min;
    int sec;
public:
    TimerComponent() = delete;
    explicit TimerComponent(int top) : curTimeSecond(top)
    {
        freeze=false;
    };
    void init() override
    {
        LI=&entity->getComponent<LabelInterface>();
        LI->ChangeText(std::to_string(curTimeSecond));
        LI->SetText();
        isActive=false;
    }
    void update() override
    { 
        if(curTimeSecond>=0)
        {
            int cur = getTicks()/1000;
            if(lastTime!=cur)
            {
                curTimeSecond-=cur-lastTime;
                lastTime=cur;

                LI->ChangeText(std::to_string(curTimeSecond));
                LI->SetText();
            }
        }
        else
        {
            entity->manager.freezeALL();
            LabelInterface::MakeActiveGroup(2);
        }
        
    }   
    void start()
    {
        isActive = true;
        freeze = false;

        mStartTicks=SDL_GetTicks();
        mPausedTicks=0;
    };
    void stop()
    {
        isActive=false;
        freeze=false;
        mStartTicks=0;
        mPausedTicks=0;
    };
    void pause()
    {

        freeze = true;
        mPausedTicks = SDL_GetTicks()- mStartTicks;
        mStartTicks = 0;

    };
    void unpause()
    {
        freeze = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    };
    Uint32 getTicks()
    {
        Uint32 time = 0;
        if(isActive)
        {
            if(freeze)
            {
                time=mPausedTicks;
            }
            else
            {
                time = SDL_GetTicks() - mStartTicks;
            }
        }
        return time;
    };

   bool isStarted() const
    {
        return isActive;
    }

    bool isPaused() const
    {
        return freeze && isActive;
    }
};
