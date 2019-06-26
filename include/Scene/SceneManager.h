#pragma once
#include "ECS/Components.h"

class Scene;
class SceneManager;


constexpr std::size_t maxScene = 5;
using SceneVectorUniquePtr = std::vector<std::unique_ptr<Scene>>;
using EntityReferenceVector = std::vector<std::reference_wrapper<Entity>>;
using SceneID = std::size_t;


class Scene
{
protected:
    Manager& manager;
    EntityReferenceVector EntitiesVector;
public:
    Scene() = delete;
    Scene(Manager* man) : manager(*man) {};

    virtual void init() = 0; //create and init all entities
    virtual void render() = 0;
    virtual void update() = 0; //update all entities
    virtual void destroy() = 0;
    virtual ~Scene() = default;
};

enum SceneLabel : std::size_t
{
    Menu, Play
};

class SceneManager
{ 
private:
    SceneVectorUniquePtr SceneArray;
    SceneID activeScene=0;
public:
    
    void update()
    {
        SceneArray[activeScene]->update();
    };
    void render()
    {
        SceneArray[activeScene]->render();
    };
    template<class T>
    void addScene(Manager *manager)
    {
        std::unique_ptr<Scene> uPtr { new T(manager) };
        SceneArray.push_back(std::move(uPtr));
    }
    void changeActiveScene(SceneID id)
    {
        SceneArray[activeScene]->destroy();
        activeScene = id;
        SceneArray[activeScene]->init();
    }

};

