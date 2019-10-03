#pragma once
#include "SceneManager.h"
#include "ECS/Components.h"


class Scene_Menu : public Scene
{
private:
    enum groupRenderLabels : size_t
    {
        groupBack, groupPlayer, groupWaves,groupText, groupCursor, GROUP_COUNT
    };
     enum Entities : size_t
    {
       BackPic, Player, Waves, Play, Records, Fullscreen, Exit, Name, Typed, Cursor, TableFirst=10, TableLast=27, ENTITIES_COUNT
    };
    bool isPressed=false;
    SDL_Color color = {255,255,255};
public:
    explicit Scene_Menu(Manager* manager) : Scene(manager) {};

    void init()
    {
        isPressed=false;
        for(size_t i=0; i<ENTITIES_COUNT;i++)
        {
            EntitiesVector.push_back(this->manager.addEntity());
        }
        EntitiesVector[BackPic].get().addComponent<TransformComponent>(0.0f,0.0f,800,600,1);
        EntitiesVector[BackPic].get().addComponent<SpriteComponent>("assets/menu.png", false);
        EntitiesVector[BackPic].get().addGroup(groupBack);

 

        EntitiesVector[Play].get().addComponent<LabelInterface>(50,150, "Play", "assets/ka1.ttf", 25, color,0).SetText();
        EntitiesVector[Play].get().addGroup(groupText);

        EntitiesVector[Records].get().addComponent<LabelInterface>(50,200, "Records", "assets/ka1.ttf", 25, color,0).SetText();
        EntitiesVector[Records].get().addGroup(groupText);

        EntitiesVector[Fullscreen].get().addComponent<LabelInterface>(50,250, "Fullscreen", "assets/ka1.ttf", 25, color,0).SetText();
        EntitiesVector[Fullscreen].get().addGroup(groupText);

        EntitiesVector[Exit].get().addComponent<LabelInterface>(50,300, "Exit", "assets/ka1.ttf", 25, color,0).SetText();
        EntitiesVector[Exit].get().addGroup(groupText);
        LabelInterface::MakeActiveGroup(0);

        EntitiesVector[Name].get().addComponent<LabelInterface>(100,150,"Player Name :", "assets/ka1.ttf", 25, color, 2).SetText();
        EntitiesVector[Name].get().addGroup(groupText);
        EntitiesVector[Typed].get().addComponent<LabelInterface>(50,200," ", "assets/ka1.ttf", 25, color, 2).SetText();
        EntitiesVector[Typed].get().addGroup(groupText);

        EntitiesVector[Cursor].get().addComponent<TransformComponent>(0.0f,0.0f,64,64,1);
        EntitiesVector[Cursor].get().addComponent<SpriteComponent>("assets/good_apple.png", false);
        EntitiesVector[Cursor].get().addGroup(groupCursor);

        EntitiesVector[Cursor].get().addComponent<PlayerNameEvent>(1).freeze=true;
        EntitiesVector[Cursor].get().addComponent<AudioComponent>("assets/smb_stomp.wav",0);
        EntitiesVector[Cursor].get().addComponent<MenuController>(0,3);

        EntitiesVector[TableFirst].get().addComponent<LabelInterface>(350,0,"ScoreTable","assets/ka1.ttf", 30,color,3).SetText();
        EntitiesVector[TableFirst+1].get().addComponent<LabelInterface>(320,50,"Name", "assets/ka1.ttf", 25,color,3).SetText();
        EntitiesVector[TableFirst+2].get().addComponent<LabelInterface>(520,50,"Score", "assets/ka1.ttf", 25,color,3).SetText();
        EntitiesVector[TableFirst].get().addGroup(groupText);
        EntitiesVector[TableFirst+1].get().addGroup(groupText);
        EntitiesVector[TableFirst+2].get().addGroup(groupText);

        auto ref = Game::score_table.GetScoreTable();
        size_t y=100;
        for(size_t i=TableFirst+3, j=0;i<TableLast && j<ref.size(); i+=2, j++)
        {
            if(ref[j].second == -1) break;
            EntitiesVector[i].get().addComponent<LabelInterface>(300,y,ref[j].first, "assets/ka1.ttf", 25,color,3).SetText();
            EntitiesVector[i+1].get().addComponent<LabelInterface>(540,y,std::to_string(ref[j].second), "assets/ka1.ttf", 25,color,3).SetText();
            EntitiesVector[i].get().addGroup(groupText);
            EntitiesVector[i+1].get().addGroup(groupText);
            y+=50;
        }
        EntitiesVector[TableLast].get().addComponent<LabelInterface>(300,y,"Esc to back to Menu", "assets/ka1.ttf", 25, color,3).SetText();
        EntitiesVector[TableLast].get().addGroup(groupText);



        

        



    }
    void eventHandler() override
    {
        if(Game::event.type == SDL_KEYDOWN && LabelInterface::isActiveGroup(3))
        {
            if(Game::event.key.keysym.sym == SDLK_ESCAPE && isPressed)
            {
                LabelInterface::KillGroup(3);
                EntitiesVector[Cursor].get().unHold();
                LabelInterface::MakeActiveGroup(0);
                isPressed=false;
            }
        }
        if(Game::event.type == SDL_KEYUP)
        {
            if(Game::event.key.keysym.sym == SDLK_RETURN)
                isPressed = true;
        }
    }
    void update() override
    {

    }
    void render() override
    {

        for(size_t i=0; i < GROUP_COUNT; i++)
        {
            auto& group(manager.GetGroup(i));
            for(auto &e:group)
            {
                e->draw();
            }
        }
    }
    void destroy() override
    {
        EntitiesVector.clear();
        manager.destroy();
    }

};