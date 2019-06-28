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
       BackPic, Player, Waves, Play, Records, Fullscreen, Exit, Name, Typed, Cursor, TableFirst=10, TableLast=22, ENTITIES_COUNT
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
        EntitiesVector[BackPic].get().addComponent<SpriteComponent>("assets/menuback.png", false);
        EntitiesVector[BackPic].get().addGroup(groupBack);

        EntitiesVector[Waves].get().addComponent<TransformComponent>(0.0f,430.0f,800,64,2);
        EntitiesVector[Waves].get().addComponent<SpriteComponent>("assets/waves.png", true);
        EntitiesVector[Waves].get().getComponent<SpriteComponent>().setAnim("Idle", 0,800, 30, AnimationFunctions::CarriageAnimation); 
        EntitiesVector[Waves].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Waves].get().addGroup(groupWaves);

        EntitiesVector[Player].get().addComponent<TransformComponent>(400.0f,200.0f,64,64,5);
        EntitiesVector[Player].get().addComponent<SpriteComponent>("assets/MenuPlayerAnim.png", true);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 8, 250);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Play", 1, 8, 250, AnimationFunctions::PlusAnimation);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Player].get().addGroup(groupPlayer);

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

        EntitiesVector[Cursor].get().addComponent<TransformComponent>(0.0f,0.0f,32,32,1);
        EntitiesVector[Cursor].get().addComponent<SpriteComponent>("assets/MenuCursor.png", false);
        EntitiesVector[Cursor].get().addGroup(groupCursor);

        EntitiesVector[Cursor].get().addComponent<PlayerNameEvent>(EntitiesVector[Player].get(), 1).freeze=true;
        EntitiesVector[Cursor].get().addComponent<MenuController>(0,3);

        EntitiesVector[TableFirst].get().addComponent<LabelInterface>(350,0,"ScoreTable","assets/ka1.ttf", 30,color,3).SetText();
        EntitiesVector[TableFirst+1].get().addComponent<LabelInterface>(300,50,"Name       Score", "assets/ka1.ttf", 25,color,3).SetText();
        EntitiesVector[TableFirst].get().addGroup(groupText);
        EntitiesVector[TableFirst+1].get().addGroup(groupText);

        auto vec=Game::score_table.GetScoreTable();
        size_t count;
        if(vec.size()<TableLast-TableFirst-3) count = vec.size()+TableFirst+2;
        else count = TableLast;
        size_t j=2;
        for(size_t i=TableFirst+2,k=0; i<count; i++,k++)
        {
            EntitiesVector[i].get().addComponent<LabelInterface>(350,50*j,vec[k].first+"        "+std::to_string(vec[k].second),
                "assets/ka1.ttf", 20, color, 3).SetText();
            EntitiesVector[i].get().addGroup(groupText);
            j++;
        }
        EntitiesVector[TableLast].get().addComponent<LabelInterface>(300,50*j, "Press Escape",
                "assets/ka1.ttf", 20, color, 3).SetText();
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
        //Make erase deleted Entities

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