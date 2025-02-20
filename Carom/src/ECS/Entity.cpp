#include "Component.h"
#include "Entity.h"

#include <algorithm>

using namespace std;

namespace ecs {

    Entity::Entity(GameScene& scene) : _myScene(scene), _alive(true)
    {
    }

    Entity::~Entity(){
        for(Component* component : _currentComponents) 
            delete component;
    }

    void Entity::enable() {
        for(auto& cmp: _currentComponents)
            cmp->setEnable(true);
    }

    void Entity::disable() {
        for(auto& cmp: _currentComponents)
            cmp->setEnable(false);
    }

    void Entity::setListAnchor(GameList<Entity>::anchor&& anchor){
        this->_anchor = std::move(anchor);
    }

    void Entity::update(){
        for(Component* component : _currentComponents)
            if (component->isEnable()) component->update();
    }

    void Entity::render(){
        for(Component* component : _currentComponents) 
            if (component->isEnable()) component->render();
    }

    void Entity::handleEvents(){
        for(Component* component : _currentComponents) 
            if (component->isEnable()) component->handleEvent();
    }
}