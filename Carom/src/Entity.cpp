#include "Entity.h"

#include "Component.h"

using namespace std;

ecs::Entity::Entity() : _alive(true)
{
    
}

ecs::Entity::~Entity(){
    for(Component* component : _currentComponents) delete component;
}

bool ecs::Entity::addComponent(Component* component, ComponentID ID){
    if(_components[ID] == nullptr) return false;

    _components[ID] = component;
    _currentComponents.push_back(component);

    return true;
}

bool ecs::Entity::removeComponent(ComponentID ID){
    if(_components[ID] == nullptr) return false;

    auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[ID]);
    _currentComponents.erase(it);
    _components[ID] = nullptr;

    return true;
}

bool ecs::Entity::tryGetComponent(ComponentID ID, Component*& component){
    if(_components[ID] == nullptr) return false;

    component = _components[ID];
    return true;
}

void ecs::Entity::update(){
    for(Component* component : _currentComponents) component->update(this);
}

void ecs::Entity::render(){
    for(Component* component : _currentComponents) component->render(this);
}

void ecs::Entity::handleEvents(){
    for(Component* component : _currentComponents) component->handleEvent(this);
}