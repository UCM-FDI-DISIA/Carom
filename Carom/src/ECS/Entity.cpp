
#include "Component.h"
#include "Entity.h"

#include <algorithm>

using namespace std;

namespace ecs {

    Entity::Entity() : _alive(true)
    {
    }

    Entity::~Entity(){

        for(Component* component : _currentComponents) 
            delete component;
    }

    bool Entity::addComponent(Component* component, ComponentID ID){
        if(_components[ID] != nullptr) return false;

        _components[ID] = component;
        _currentComponents.push_back(component);

        return true;
    }

    bool Entity::removeComponent(ComponentID ID){

        if(_components[ID] == nullptr) return false;

        auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[ID]);
        _currentComponents.erase(it);
        _components[ID] = nullptr;

        return true;
    }

    bool Entity::tryGetComponent(ComponentID ID, Component*& component){
        if(_components[ID] == nullptr) return false;

        component = _components[ID];
        return true;
    }

    void Entity::update(){
        for(Component* component : _currentComponents) 
            component->update(this);
    }

    void Entity::render(){
        for(Component* component : _currentComponents) component->render(this);
    }

    void Entity::handleEvents(){
        for(Component* component : _currentComponents) component->handleEvent(this);
    }
}