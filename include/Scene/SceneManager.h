#pragma once
#include "ECS/ECS.h"

class Scene;


constexpr std::size_t maxScene = 5;
using SceneVectorUniquePtr = std::vector<std::unique_ptr<Scene>>;
using EntityReferenceVector = std::vector<std::reference_wrapper<Entity>>;
using SceneID = std::size_t;


class Scene
{

public:
    Manager& manager;
    EntityReferenceVector EntitiesVector;
    Scene() = delete;
    Scene(Manager* man) : manager(*man) {};

    virtual void init() = 0; //create and init all entities
    virtual void eventHandler() = 0;
    virtual void render() = 0;
    virtual void update() = 0; //update all entities
    virtual void destroy() = 0;
    virtual ~Scene() = default;
};

enum SceneLabel : std::size_t
{
    Menu, Play
};

inline SceneID getNewSceneTypeID()
{
    static SceneID lastID=0u;
    return lastID++;
}

template<class T>
inline SceneID getSceneTypeID()
{
    static SceneID typeID = getNewSceneTypeID();
    return typeID;
}
constexpr std::size_t MaxScenes = 5;

using SceneBitSet = std::bitset<MaxScenes>;

class SceneManager
{ 
private:
    SceneBitSet sceneBitSet;
    SceneVectorUniquePtr SceneArray;
    SceneID activeScene=0;
    SceneID lastID=-1;
    bool change=false;
public:
    void event()
    {
        if(change)
        {
            SceneArray[lastID]->manager.refresh();
            SceneArray[activeScene]->init(); 
            change=false;
        }
        SceneArray[activeScene]->eventHandler();
    };
    void update()
    {
        SceneArray[activeScene]->manager.update();
        SceneArray[activeScene]->update();
    };
    void render()
    {
        SceneArray[activeScene]->render();
    };
    template<class T>
    void addScene(Manager *manager)
    {
        sceneBitSet[getSceneTypeID<T>()] = true;
        std::unique_ptr<Scene> uPtr { new T(manager) };
        SceneArray.push_back(std::move(uPtr));
    }
    void changeActiveScene(SceneID id)
    {
        SceneArray[activeScene]->destroy();
        lastID = activeScene;
        activeScene = id;

        change = true;
    }
    template<class T>  
    T& getScene()
    {
        return SceneArray[getSceneTypeID<T>()];
    }

};

