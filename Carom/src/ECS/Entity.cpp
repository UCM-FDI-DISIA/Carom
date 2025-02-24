#include "Component.h"
#include "Entity.h"
#include "ITransform.h"

#include <algorithm>

using namespace std;

namespace ecs {

    Entity::Entity(GameScene& scene) : _myScene(scene), _alive(true), _myTransform(nullptr)
    {
    }

    Entity::~Entity(){
        for(Component* component : _currentComponents) 
            delete component;
    }

    void Entity::setListAnchor(GameList<Entity>::anchor&& anchor){
        this->_anchor = std::move(anchor);
    }

    void Entity::update(){
        for(Component* component : _currentComponents) 
            component->update();
    }

    void Entity::render(Camera* camera){
        for(Component* component : _currentComponents) 
            component->render(camera);
    }

    void Entity::handleEvents(){
        for(Component* component : _currentComponents) 
            component->handleEvent();
    }

    GameScene& Entity::getScene(){
        return _myScene;
    }
}