#include "Component.h"
#include "Entity.h"
#include "ITransform.h"
#include "RenderTextureComponent.h"
#include "GameScene.h"

#include <algorithm>

using namespace std;

Entity::Entity(GameScene& scene, grpId_t gId) : _myScene(scene), _alive(true), _myTransform(nullptr)
{
    _myScene.getEntities().push_back(this);
    _myScene.getEntitiesOfGroup(gId).push_back(this);
}

Entity::~Entity(){
    for(Component* component : _currentComponents) 
        delete component;
}

template<>
bool Entity::addComponent<RenderTextureComponent>(RenderTextureComponent* renderComp) {
    
    if(_components[cmpId<RenderTextureComponent>] != nullptr) return false;

    _myScene.getRenderEntities().push_back(this);

    _components[cmpId<RenderTextureComponent>] = renderComp;
    _currentComponents.push_back(renderComp);
    _components[cmpId<RenderTextureComponent>]->init();


    return true;
}

template <>
bool Entity::removeComponent<RenderTextureComponent>() {
    if(_components[cmpId<RenderTextureComponent>] == nullptr) return false;

    auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[cmpId<RenderTextureComponent>]);
    _currentComponents.erase(it);
    _components[cmpId<RenderTextureComponent>] = nullptr;

    auto& entsRenderable = _myScene.getRenderEntities();
    auto itR = find(entsRenderable.begin(), entsRenderable.end(), this);
    entsRenderable.erase(itR);

    return true;
}

void Entity::activate() {
    for(auto& cmp: _currentComponents)
        cmp->setEnabled(true);
}

void Entity::deactivate() {
    for(auto& cmp: _currentComponents)
        cmp->setEnabled(false);
}

void Entity::setListAnchor(GameList<Entity>::anchor&& anchor){
    this->_anchor = std::move(anchor);
}

void Entity::update(){
    for(Component* component : _currentComponents)
        if (component->isEnabled()) component->update();
}

void Entity::render(){
    for(Component* component : _currentComponents) 
        if (component->isEnabled()) component->render();
}

void Entity::handleEvents(){
    for(Component* component : _currentComponents) 
        if (component->isEnabled()) component->handleEvent();
}

GameScene& Entity::getScene(){
    return _myScene;
}