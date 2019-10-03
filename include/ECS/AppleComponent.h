#pragma once

#include "ECS/ECS.h"




class AppleComponent : public Component
{
private:
    int point;
public:
    int GetScore() const
    {
        return point;
    }
    void SetPoint(int point)
    {
        this->point = point;
    }
};