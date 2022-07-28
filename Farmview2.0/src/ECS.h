#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

/*
    Entity-Component-System (ECS) is a type of game architecture that focuses on composing 
    entities with data only components, and processing logic separately in systems.
*/

// Forward declarations of component, entity, and manager classes:
class Component;
class Entity;
class Manager;

// Creating custom types of unsigned long long:
using ComponentID = std::size_t;
using Group = std::size_t;

// Function that returns returns static variable, last component id
// Everytime we call this function, the value of lastID increase and returns that value.
inline ComponentID getNewComponentTypeID ()
{
    static ComponentID lastID = 0u;
    return lastID++;
}

// Attaches ComponentID by creating a template function that takes the component as a type
// creates a specific id for the component depending on the type and will always return the
// same value. "noexcept" - No exception if it crashes
template<typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

// Max number of components per entity: 
constexpr std::size_t maxComponents = 32;

// Max number of groups:
constexpr std::size_t maxGroups = 32;

// Bitsets:
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

// Array of component points with length of maxComponents
using ComponentArray = std::array<Component*, maxComponents>;

class Component
/* Game components will inherit from this class */
{
public:
    //Use a pointer to store the parent entity:
    Entity* entity{ nullptr }; 

    // Virtual methods that will be overridden by game component types:
    virtual void init() {}
    virtual void update(){}
    virtual void draw(){}

    // Destructor:
    virtual ~Component(){}
};

class Entity
 /* 
     Aggregate of components with methods that will help update and draw 
     all components = container of components with methods to add/update/draw
     components.
 */
{
public:
    // Function that updates and draw each component in components:
    void update()
    {
        for (auto& c : components) c->update();
    }

    void draw()
    {
        for (auto& c : components) c->draw();
    }

    // Control the lifetime of the entity: 
    bool isActive() { return active; }
    void destroy() { active = false; }

    // Check if entity has components and return true or false if the component is attached:
    template <typename T> 
    bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>()];
    }

    // Add components to our entity: 
    // "T" is the component type. 
    // "TArgs" is a parameter pack of types used to contruct the component
    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&...mArgs)
    {
        // Allocating component of type "T" on the heap by forwarding 
        // the passed argumrnets to its constructor: 
        T* c(new T(std::forward<TArgs>(mArgs)...));

        // Set the component's entity to the current instance with the 
        // "this" pointer:
        c->entity = this;

        // We will wrap the raw pointer into a smart pointer, so that we can
        // emplace it into our container and to make sure we do not leak
        // any memory: 
        std::unique_ptr<Component> uPtr{ c };

        // Add the smart pointer  to our container:
        // (use std::move because std:unique_pter cannot be copied)
        components.emplace_back(std::move(uPtr));

        // Add position component will always be put in the same positon in the
        // array:
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();

        // Return a reference to the newly added component:
        return *c;
    }

    template<typename T>
    T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }

    // Check if the entity is in a group and returns true or false:
    bool hasGroup(Group mGroup)
    {
        return groupBitSet[mGroup];
    }
    
    // Add entity to a group:
    void addGroup(Group mGroup);

    // Delete entity from a group:
    void deleteGroup(Group mGroup)
    {
        groupBitSet[mGroup] = false;
    }

    Entity(Manager& mManager) : manager(mManager)
    {

    }

private: 
    // References to the manager object:
    Manager& manager;

    // Keep track of whether the entity is alive or dead with a boolean:
    bool active = { true };

    // Store the components in a vector to allow polymorphism:
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;
};

class Manager
/* Aggregate of entities. */
{
public:
    // Updates by first cleaning up "dead" entities then loop through 
    // the "alive" entities and update them:
    // (memory will be freed because they are wrapped in unique_ptrs)
    void update()
    {
        entities.erase(
            std::remove_if(std::begin(entities),
            std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isActive();
            }),
            std::end(entities));

        for (auto& e : entities) e->update();
    }

    // Draw alive entities:
    void draw()
    {
        for (auto& e : entities) e->draw();
    }

    // Removes dead entities and dead entities from groups:
    void refresh()
    {
        // Removes entity from group:
        for (auto i(0u); i < maxGroups; i++)
        {
            auto& vector(groupedEntities[i]);
            vector.erase(
                std::remove_if(std::begin(vector), std::end(vector),
                    [i](Entity* mEntity)
                    {
                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                    }),
                std::end(vector));
        }

        // Removes dead entities:
        entities.erase(std::remove_if(std::begin(entities),
            std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
            {
                return !mEntity->isActive();
            }),
            std::end(entities));
    }

    // Add entity to group:
    void addToGroup(Entity* mEntity, Group mGroup)
    {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    // Get a list of entities inside of a group:
    std::vector<Entity*>& getGroup(Group mGroup)
    {
        return groupedEntities[mGroup];
    }

    // Add entity:
    // First allocate new memory in the heap
    // Then wraps entity in an unique pointer
    // Lastly, places the entity is back into the entity storage
    // Finally, returns entity 
    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));

        return *e;
    }

private:
    // Storage for entities:
    std::vector<std::unique_ptr<Entity>> entities;

    // Array of vectors with group of entities:
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;

};

#endif