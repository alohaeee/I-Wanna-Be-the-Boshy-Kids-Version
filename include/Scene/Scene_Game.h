#pragma once 
#include "SceneManager.h"
#include "ECS/Components.h"
#include "Game.h"

class Scene_Game : public Scene
{
private:
    enum groupRenderLabels : size_t
    {
        groupBack, groupPlayer, groupText,groupString, groupApples, groupWaves, groupFilter, groupPause, GROUP_COUNT
    };
    enum Entities : size_t
    {
        BackPic, Cloud_L, Cloud_M, Cloud_R, Timer, Name, Score,Waves, Player, String, Filter, First_Fish=11, Last_Fish=21 , Resume, Exit, Cursor, GameOver, PressEnter, ENTITIES_COUNT
    };
    SDL_Color color={255,255,255};
    bool startTimer=false;
    bool Paused=false;
    bool END=false;
public:
    explicit Scene_Game(Manager* manager) : Scene(manager) {};
    void init() override
    {
        EntitiesVector.clear();
        startTimer=false;
        Paused=false;
        END=false;
        for(size_t i=0; i < ENTITIES_COUNT; i++)
        {
            EntitiesVector.push_back(this->manager.addEntity());
        }
        
        EntitiesVector[BackPic].get().addComponent<TransformComponent>(0.0f,0.0f,800,600,1); 
        EntitiesVector[BackPic].get().addComponent<SpriteComponent>("assets/background.jpg");
        EntitiesVector[BackPic].get().addComponent<ColliderComponent>("Wall");
        EntitiesVector[BackPic].get().addGroup(groupBack);
      
        // EntitiesVector[Cloud_L].get().addComponent<TransformComponent>(50.0f,0.0f,64,32,3);
        // EntitiesVector[Cloud_L].get().addComponent<SpriteComponent>("assets/cloud_one.png", true);
        // EntitiesVector[Cloud_L].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 12, 1000,AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Cloud_L].get().getComponent<SpriteComponent>().Play("Idle");
        // EntitiesVector[Cloud_L].get().addGroup(groupBack);

        // EntitiesVector[Cloud_M].get().addComponent<TransformComponent>(300.0f,0.0f,64,32,3);
        // EntitiesVector[Cloud_M].get().addComponent<SpriteComponent>("assets/cloud_one.png", true);
        // EntitiesVector[Cloud_M].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 12, 700, AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Cloud_M].get().getComponent<SpriteComponent>().Play("Idle");
        // EntitiesVector[Cloud_M].get().addGroup(groupBack);

        // EntitiesVector[Cloud_R].get().addComponent<TransformComponent>(550.0f,0.0f,64,32,3);
        // EntitiesVector[Cloud_R].get().addComponent<SpriteComponent>("assets/cloud_one.png", true);
        // EntitiesVector[Cloud_R].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 12, 1000, AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Cloud_R].get().getComponent<SpriteComponent>().Play("Idle");
        // EntitiesVector[Cloud_R].get().addGroup(groupBack);
      
        // EntitiesVector[Waves].get().addComponent<TransformComponent>(0.0f,250.0f,800,64,1);
        // EntitiesVector[Waves].get().addComponent<SpriteComponent>("assets/waves.png", true);
        // EntitiesVector[Waves].get().getComponent<SpriteComponent>().setAnim("Idle", 0,800, 30, AnimationFunctions::CarriageAnimation); 
        // EntitiesVector[Waves].get().getComponent<SpriteComponent>().Play("Idle");
        // EntitiesVector[Waves].get().addGroup(groupWaves);

        // EntitiesVector[Filter].get().addComponent<TransformComponent>(0.0f,0.0f,800,600,1);
        // EntitiesVector[Filter].get().addComponent<SpriteComponent>("assets/water.png");
        // EntitiesVector[Filter].get().getComponent<SpriteComponent>().setAlpha(70);
        // EntitiesVector[Filter].get().addGroup(groupFilter);
        
        ////////
        ///ui
        /////
        EntitiesVector[Timer].get().addComponent<LabelInterface>(125,95, " ", "assets/ka1.ttf", 20,color,0).SetText();
        EntitiesVector[Timer].get().addComponent<TimerComponent>(20).start();
        EntitiesVector[Timer].get().addGroup(groupText);

        EntitiesVector[Name].get().addComponent<LabelInterface>(360,95,Game::score_table.getName(), "assets/ka1.ttf", 20,color, 0);
        EntitiesVector[Name].get().getComponent<LabelInterface>().SetText();
        EntitiesVector[Name].get().addGroup(groupText);
        EntitiesVector[Score].get().addComponent<LabelInterface>(630,95," ","assets/ka1.ttf", 20, color, 0).SetText();
        EntitiesVector[Score].get().addGroup(groupText);

        EntitiesVector[GameOver].get().addComponent<LabelInterface>(0,200,"Game Over", "assets/ka1.ttf", 30,color,2).SetText();
        EntitiesVector[GameOver].get().addGroup(groupPause);

        EntitiesVector[PressEnter].get().addComponent<LabelInterface>(0,300,"Press Enter to exit", "assets/ka1.ttf", 30,color,2).SetText();
        EntitiesVector[PressEnter].get().addGroup(groupPause);
        /////////////////
        ///Player
        ////////////////
        EntitiesVector[Player].get().addComponent<TransformComponent>(350.0f,500.0f, 64,64,2).speed=4;
        EntitiesVector[Player].get().addComponent<SpriteComponent>("assets/basket.png", false); //.setAnim("Idle",0,6,200, AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Player].get().getComponent<SpriteComponent>().Play("Idle");
        // EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Walk", 1, 7, 200, AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Action", 2, 7, 150, AnimationFunctions::PlusAnimation);
        // EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("AfterIdle", 3, 6, 200, AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Arrow", 4, 4, 200, AnimationFunctions::TicksMultiplyAnimation);
        // EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("AfterWalk", 5, 7, 200, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Player].get().addComponent<KeyboardComponent>();
        EntitiesVector[Player].get().addComponent<ColliderComponent>("Player").MakeCollPair("Wall", Collision::LRC,ColHandler::LeftVelocityZero);
        EntitiesVector[Player].get().addComponent<ScoreComponent>(EntitiesVector[Score].get());
        EntitiesVector[Player].get().addGroup(groupPlayer);

        // EntitiesVector[String].get().addComponent<TransformComponent>(0.0f,0.0f,64,0,2).speed=2;;
        // EntitiesVector[String].get().addComponent<SpriteComponent>("assets/string.png");
        // EntitiesVector[String].get().addComponent<ColliderComponent>("String", ColliderUpdateFunc::TransfromHOOKCollider);
        // EntitiesVector[String].get().addGroup(groupString);

        //EntitiesVector[String].get().addComponent<ScoreComponent>(EntitiesVector[Score].get());
        // EntitiesVector[String].get().addComponent<MainAction>(EntitiesVector[Player].get());
        
        

        ////////////////
        ////Fishies
        ///////////////

        for(size_t Fish_ID=First_Fish; Fish_ID<=Last_Fish;Fish_ID++)
        {
            EntitiesVector[Fish_ID].get().addComponent<TransformComponent>(0.0f,0.0f,64,64,1);
            EntitiesVector[Fish_ID].get().addComponent<SpriteComponent>("assets/apple_asset.png", true).setAnim("Good_Apple", 0, 1, 200);
            EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Bad_Apple", 1, 1, 200);
            // EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Idle_Emerald", 2, 8, 200);
            // EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Catched_Emerald", 3, 6, 200);
            // EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Idle_Rubbish", 4, 8, 200);
            // EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Catched_Rubbish", 5, 6, 200);
            std::string Collider_Tag = "Fish_"+std::to_string(Last_Fish - Fish_ID + 1);
            EntitiesVector[Fish_ID].get().addComponent<ColliderComponent>(Collider_Tag, ColliderUpdateFunc::TransfromFISHCollider);
            EntitiesVector[Fish_ID].get().getComponent<ColliderComponent>().MakeCollPair("Wall",Collision::reAABB, ColHandler::ReRandPosFishies);
            EntitiesVector[Fish_ID].get().getComponent<ColliderComponent>().MakeCollPair("Player",Collision::AABB, ColHandler::BasketCollision);
            EntitiesVector[Fish_ID].get().addComponent<AppleComponent>();
            EntitiesVector[Fish_ID].get().addComponent<SpawnComponent>().RandPos();
            
            EntitiesVector[Fish_ID].get().addGroup(groupApples);
        }        
        LabelInterface::MakeActiveGroup(0);

        EntitiesVector[Resume].get().addComponent<LabelInterface>(340,220,"Resume", "assets/ka1.ttf", 30, color, 1).SetText();
        EntitiesVector[Exit].get().addComponent<LabelInterface>(340,300,"Exit", "assets/ka1.ttf", 30, color,1).SetText();
        EntitiesVector[Resume].get().addGroup(groupPause);
        EntitiesVector[Exit].get().addGroup(groupPause);
        
        EntitiesVector[Cursor].get().addComponent<TransformComponent>(0.0f,0.0f,64,64,2);
        EntitiesVector[Cursor].get().addComponent<SpriteComponent>("assets/good_apple.png", false);
        EntitiesVector[Cursor].get().addComponent<SubMenuController>(0,1);
        EntitiesVector[Cursor].get().addGroup(groupPause);
        EntitiesVector[Cursor].get().Hold();

    }
    void eventHandler() override
    {
        if(LabelInterface::isActiveGroup(2))
        {
            END=true;
            if(Game::event.key.keysym.sym == SDLK_RETURN)
            {
                Game::score_table.PushScore(EntitiesVector[Player].get().getComponent<ScoreComponent>().getScore());
                Game::score_table.UpdateFile();
                EntitiesVector[GameOver].get().sceneManager.changeActiveScene(0);
            }
        }
        
        if(Paused&&!EntitiesVector[Cursor].get().getComponent<TransformComponent>().isActive)
        {
            EntitiesVector[Timer].get().getComponent<TimerComponent>().unpause();
            Paused=false;
        }
        if(Game::event.type==SDL_KEYDOWN && !END)
        {
            switch(Game::event.key.keysym.sym)
            {
                case SDLK_SPACE:
                    // if(!startTimer)
                    // {
                    //     EntitiesVector[Timer].get().getComponent<TimerComponent>().start();
                    //     startTimer=true;
                    // }       
                    break;
                case SDLK_ESCAPE:
                    if(!EntitiesVector[Cursor].get().getComponent<TransformComponent>().isActive)
                    {
                        for(auto &e:EntitiesVector)
                        {
                            e.get().FreezeEntity();
                        }
                        LabelInterface::MakeActiveGroup(1);
                        EntitiesVector[Cursor].get().unHold();
                        EntitiesVector[Cursor].get().UnFreezeEntity();
                        Paused=true;
                        EntitiesVector[Timer].get().getComponent<TimerComponent>().pause();
                    }
                    break;
            
            }

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
       
        manager.destroy();
        
    }

    ~Scene_Game() {};
};