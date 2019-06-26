#pragma once 
#include "SceneManager.h"
#include "Collision.h"

class Scene_Game : public Scene
{
private:
    enum groupRenderLabels : size_t
    {
        groupBack, groupPlayer, groupString, groupFishies, groupWaves, groupFilter, GROUP_COUNT
    };
    enum Entities : size_t
    {
        BackPic, Cloud_L, Cloud_M, Cloud_R, Waves, Player, String, Filter, First_Fish=8, Last_Fish=18 , ENTITIES_COUNT
    };
public:
    Scene_Game(Manager* manager) : Scene(manager) {};
    void init() override
    {
        for(size_t i=0; i < ENTITIES_COUNT; i++)
        {
            EntitiesVector.push_back(this->manager.addEntity());
        }
        
        EntitiesVector[BackPic].get().addComponent<TransformComponent>(0.0f,0.0f,800,600,1); 
        EntitiesVector[BackPic].get().addComponent<SpriteComponent>("assets/background.png");
        EntitiesVector[BackPic].get().addComponent<ColliderComponent>("Wall");
        EntitiesVector[BackPic].get().addGroup(groupBack);
      
        EntitiesVector[Cloud_L].get().addComponent<TransformComponent>(50.0f,0.0f,64,32,3);
        EntitiesVector[Cloud_L].get().addComponent<SpriteComponent>("assets/cloud_one.png", true);
        EntitiesVector[Cloud_L].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 12, 1000,AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Cloud_L].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Cloud_L].get().addGroup(groupBack);

        EntitiesVector[Cloud_M].get().addComponent<TransformComponent>(300.0f,0.0f,64,32,3);
        EntitiesVector[Cloud_M].get().addComponent<SpriteComponent>("assets/cloud_one.png", true);
        EntitiesVector[Cloud_M].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 12, 700, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Cloud_M].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Cloud_M].get().addGroup(groupBack);

        EntitiesVector[Cloud_R].get().addComponent<TransformComponent>(550.0f,0.0f,64,32,3);
        EntitiesVector[Cloud_R].get().addComponent<SpriteComponent>("assets/cloud_one.png", true);
        EntitiesVector[Cloud_R].get().getComponent<SpriteComponent>().setAnim("Idle", 0, 12, 1000, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Cloud_R].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Cloud_R].get().addGroup(groupBack);
      
        EntitiesVector[Waves].get().addComponent<TransformComponent>(0.0f,250.0f,800,64,1);
        EntitiesVector[Waves].get().addComponent<SpriteComponent>("assets/waves.png", true);
        EntitiesVector[Waves].get().getComponent<SpriteComponent>().setAnim("Idle", 0,800, 30, AnimationFunctions::CarriageAnimation); 
        EntitiesVector[Waves].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Waves].get().addGroup(groupWaves);

        EntitiesVector[Filter].get().addComponent<TransformComponent>(0.0f,0.0f,800,600,1);
        EntitiesVector[Filter].get().addComponent<SpriteComponent>("assets/water.png");
        EntitiesVector[Filter].get().getComponent<SpriteComponent>().setAlpha(70);
        EntitiesVector[Filter].get().addGroup(groupFilter);

        /////////////////
        ///Player
        ////////////////
        EntitiesVector[Player].get().addComponent<TransformComponent>(350.0f,160.0f, 64,64,2).speed=2;
        EntitiesVector[Player].get().addComponent<SpriteComponent>("assets/player.png", true).setAnim("Idle",0,6,200, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().Play("Idle");
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Walk", 1, 7, 200, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Action", 2, 7, 150, AnimationFunctions::PlusAnimation);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("AfterIdle", 3, 6, 200, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("Arrow", 4, 4, 200, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Player].get().getComponent<SpriteComponent>().setAnim("AfterWalk", 5, 7, 200, AnimationFunctions::TicksMultiplyAnimation);
        EntitiesVector[Player].get().addComponent<KeyboardComponent>();
        EntitiesVector[Player].get().addComponent<ColliderComponent>("Player").MakeCollPair("Wall", Collision::LRC,ColHandler::LeftVelocityZero);
        EntitiesVector[Player].get().addGroup(groupPlayer);

        EntitiesVector[String].get().addComponent<TransformComponent>(0.0f,0.0f,64,0,2).speed=2;;
        EntitiesVector[String].get().addComponent<SpriteComponent>("assets/string.png");
        EntitiesVector[String].get().addComponent<ColliderComponent>("String", ColliderUpdateFunc::TransfromHOOKCollider);
        EntitiesVector[String].get().addGroup(groupString);


        EntitiesVector[Player].get().addComponent<MainAction>(EntitiesVector[String].get());

        ////////////////
        ////Fishies
        ///////////////

        for(size_t Fish_ID=First_Fish; Fish_ID<=Last_Fish;Fish_ID++)
        {
            EntitiesVector[Fish_ID].get().addComponent<TransformComponent>(0.0f,0.0f,64,64,1);
            EntitiesVector[Fish_ID].get().addComponent<SpriteComponent>("assets/fish_pack.png", true).setAnim("Idle_Purple", 0, 8, 200);
            EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Catched_Purple", 1, 6, 200);
            EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Idle_Emerald", 2, 8, 200);
            EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Catched_Emerald", 3, 6, 200);
            EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Idle_Rubbish", 4, 8, 200);
            EntitiesVector[Fish_ID].get().getComponent<SpriteComponent>().setAnim("Catched_Rubbish", 5, 6, 200);
            std::string Collider_Tag = "Fish_"+std::to_string(Last_Fish - Fish_ID + 1);
            EntitiesVector[Fish_ID].get().addComponent<ColliderComponent>(Collider_Tag, ColliderUpdateFunc::TransfromFISHCollider);
            EntitiesVector[Fish_ID].get().getComponent<ColliderComponent>().MakeCollPair("Wall",Collision::reAABB, ColHandler::ReRandPosFishies);
            EntitiesVector[Fish_ID].get().getComponent<ColliderComponent>().MakeCollPair("String",Collision::AABB, ColHandler::Empty);
            EntitiesVector[Fish_ID].get().addComponent<SpawnComponent>().RandPos();
            EntitiesVector[Fish_ID].get().addGroup(groupFishies);
        }


    }
    void update() override
    {
        manager.refresh();
        manager.update();

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