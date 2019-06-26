#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <bitset>
#include <memory>
#include <algorithm>


//pre-declaration 
class Component;
class Entity;
class Manager;

//type routine
using ComponentID = std::size_t;
using Group = std::size_t;
//Counters of maximum Components and Groups for arrays
constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

//BitSets for checking if Entity is including some Component
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;
//Arrays of Entities and Component pointers
using ComponentArray = std::array<Component *, maxComponents>;
//using GroupArray = std::array<Entity *, maxGroups>;
//Unique pointer vector of components for safely code
using ComponentUniquePtrVector = std::vector<std::unique_ptr<Component>>;


/////////////////////////////////////
//  Unique ID for each Component  //
/////////// ///////////////////////
inline ComponentID getNewComponentTypeID()
{
    static ComponentID lastID=0u;
    return lastID++;
}

template<class T>
inline ComponentID getComponentTypeID()
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

/////////////////////////////////////////////
//  Defenition of component's base class  //
/////////// ///////////////////////////////
class Component
{
public:
    Entity* entity;
    virtual void init() {};
    virtual void update() {};
    virtual void draw() {};
    virtual ~Component() {};
    bool freeze = false;
};


///////////////////////////////////////////////
//  Entity and Entity's Manager defenition  //
/////////// /////////////////////////////////
    
class Entity
{
private:
    bool active = true;
    Manager& manager;
    ComponentUniquePtrVector components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
public:
    Entity(Manager &manager) : manager(manager) {};
    void update()
    {
        for(auto &c : components) 
        {
            if(!c->freeze)
                c->update();
        }
    }
    void draw()
    {
        for(auto &c : components) c->draw();
    }
    bool isActive() const
    {
        return active;
    }
    void destroy()
    {
        active=false;
    }
    bool hasGroup(Group mGroup) const
    {
        return groupBitSet[mGroup];
    }
    void addGroup(Group mGroup);

    void delGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }
    template<class T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    template<class T, class... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeID<T>()]= c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }
    
    template<class T> T& getComponent()
    {
        if(this->hasComponent<T>()){
            auto ptr(componentArray[getComponentTypeID<T>()]);
            return *static_cast<T*>(ptr);
        }
        return *static_cast<T*>(nullptr);
    }
};

//Unique pointer vector for safely code
using EntitiesUniquePtrVector = std::vector<std::unique_ptr<Entity>>;
//Grouped Entities in array
using GroupedEntitiesArray = std::array<std::vector<Entity*> , maxGroups>;

class Manager
{
private:
    EntitiesUniquePtrVector entities;
    GroupedEntitiesArray groupedEntities;
public:
    void update()
    {
        for(auto & e: entities)
        {
            e->update();
        }
    };
    void draw()
    {
        for(auto & e: entities)
        {
            e->draw();
        }
    }

    void refresh()
    {
        for(auto i(0u); i<maxGroups; i++)
        {
             auto& v(groupedEntities[i]);
             v.erase(
                 std::remove_if(std::begin(v), std::end(v), 
                 [i](Entity* mEntity)
                 {
                    return !mEntity->isActive() || !mEntity->hasGroup(i);
                 }),
                    std::end(v)  
             );
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->isActive();
        }),
            std::end(entities));
        

    };
    
    void AddToGroup(Entity *mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    };
    
    std::vector<Entity *>& GetGroup(Group mGroup) 
    {
        return groupedEntities[mGroup];
    };

    Entity& addEntity()
    {
        Entity *e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        
        entities.emplace_back(std::move(uPtr));
        return *e;
    };

    void destroy()
    {
        entities.clear();
    }
};



