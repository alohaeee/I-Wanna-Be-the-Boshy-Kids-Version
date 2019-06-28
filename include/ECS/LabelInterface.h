#pragma once

#include "ECS.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <string>
#include "Game.h"
#include <array>

using LabelID = std::size_t;
constexpr std::size_t MaxGroupLabels = 5;

class LabelInterface : public Component
{
private:
    TTF_Font *font;
    SDL_Rect position;
    std::string Text;
    SDL_Color color; 
    SDL_Texture *texture;
    bool Blended = true;
    LabelID ID_GROUP;
    
public:
    static std::array<std::vector<LabelInterface*>,MaxGroupLabels> LabelsVector;
    explicit LabelInterface(int xpos, int ypos, std::string text,std::string path, int size, SDL_Color color, LabelID GROUP)
    {
        position.x = xpos;
        position.y = ypos;
        Text=text;
        this->color = color;
        font = TTF_OpenFont(path.c_str() ,size);
        ID_GROUP=GROUP;
    };
    ~LabelInterface()
    {
        LabelsVector[ID_GROUP].erase(std::remove_if(std::begin(LabelsVector[ID_GROUP]),std::end(LabelsVector[ID_GROUP]),
        [this](auto Label)
        {
            return this==Label;
        }), std::end(LabelsVector[ID_GROUP]));

        if(texture) SDL_DestroyTexture(texture);
        if(font) TTF_CloseFont(font);
    };
    void init() override
    {
        
        this->isActive=false;
        LabelsVector[ID_GROUP].push_back(this);
    }
    void draw() override
    {
        SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
    }
    void SetText()
    {
        SDL_Surface *tmpSurf;
        if(Blended)
            tmpSurf = TTF_RenderText_Blended(font,Text.c_str(),color);
        else tmpSurf = TTF_RenderText_Solid(font,Text.c_str(),color);
        texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurf);
        SDL_QueryTexture(texture, nullptr,nullptr, &position.w, &position.h);
        SDL_FreeSurface(tmpSurf);
    }
    void ChangeColor(const SDL_Color c)
    {
        color = c;
    }   
    void ChangeText(std::string text)
    {
        Text = text;
    }
    void TextAndColor(std::string Text,SDL_Color color)
    {
        this->Text = Text;
        this->color = color;
    }
    void ChangePos(const int x,const int y)
    {
        position.x=x;
        position.y=y;
    }
    SDL_Rect& GetPos() 
    {
        return position;
    }
    void ChangeRenderType(bool isBlended)
    {
        Blended = isBlended;
    }
    static void MakeActiveGroup(LabelID group)
    {
        for(auto &l: LabelsVector[group])
        {
            l->isActive=true;
        }
    }
    static void KillGroup(LabelID group)
    {
        for(auto &l: LabelsVector[group])
        {
            l->isActive=false;
        }
    }

    static bool isActiveGroup(LabelID ID) 
    {
        return LabelsVector[ID][0]->isActive==true;
    }
};