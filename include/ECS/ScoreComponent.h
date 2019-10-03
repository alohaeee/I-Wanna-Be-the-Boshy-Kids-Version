#pragma once
#include "ECS.h"
#include "LabelInterface.h"
#include <iostream>

class ScoreComponent : public Component
{
private:
    int score=0;
    int last_score=-1;
    LabelInterface *LI;
public:
    ScoreComponent() = delete;
    explicit ScoreComponent(Entity &E) {
        LI=&E.getComponent<LabelInterface>();
    }
    void update() override
    {
        if(score!=last_score)
        {
            LI->ChangeText(std::to_string(score));
            LI->SetText();
            last_score=score;
        }
        std::cout << score << std::endl;
    }
    int getScore()
    {
        return score;
    }
    void PlusScore(int s)
    {
        score+=s;
        std::cout << "aa" << score << std::endl;
    }
};