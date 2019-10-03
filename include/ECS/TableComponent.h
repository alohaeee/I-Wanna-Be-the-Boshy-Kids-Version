#pragma once
#include "ECS.h"
#include "SDL2/SDL.h"
#include <vector>
#include "LabelInterface.h"
#include "../Game.h"

class TableComponent : public Component
{
private:
    LabelInterface* table_name;
    std::vector<SDL_Rect> col_pos;
    SDL_Rect size;
    bool isDraw;
    LabelID id;
    int col, row;
    std::vector<std::vector<int>> col_raw;
public:
    TableComponent(int x, int y, int w, int h, LabelID id,int col, int row,bool isDraw) : id(id), isDraw(isDraw) , col(col), row(row)
    {
        size.x=x;
        size.y=y;
        size.w=w;
        size.h=h;
        
    };
    void init()
    {
        table_name=&entity->getComponent<LabelInterface>();
        LabelInterface::LabelsVector[id][0]->GetPos().x=size.x+size.w/2;
        LabelInterface::LabelsVector[id][1]->GetPos().x=size.x;
        LabelInterface::LabelsVector[id][2]->GetPos().x=size.x+size.w/2;

        

    }
    void PushCol_Pos(SDL_Rect new_col)
    {
        col_pos.push_back(new_col);
    }
    void update() override
    {
        
    }
    void draw() override
    {
        if(isDraw && LabelInterface::isActiveGroup(id))
        {
            SDL_RenderDrawRect(Game::renderer, &size);
            int one_part = size.w/col;
            for(size_t i=size.x; i < size.x+size.w; i+=one_part)
            {
                SDL_RenderDrawLine(Game::renderer,i,size.y,i,size.y+size.h);
            }
        }
    }
    void changeTableSize(SDL_Rect &dst_Rect)
    {
        size = dst_Rect;
    }
    void FillCol(std::initializer_list<std::string> raw)
    {
        for(auto &arg: raw)
        {
        
        }
    }

};