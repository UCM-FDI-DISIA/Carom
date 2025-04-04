#include "Component.h"
#include "Entity.h"
#include "ITransform.h"
#include "RenderTextureComponent.h"
#include "GameScene.h"
#include "CowboyPoolScene.h"
#include "ShadowComponent.h"

#include <algorithm>

using namespace std;


Entity::Entity(GameScene& scene, grpId_t gId) : _myScene(scene), _alive(true), _myTransform(nullptr), _id((grp::grpId)gId)
{
    _myScene.getEntities().push_back(this);
    _myScene.getEntitiesOfGroup(gId).push_back(this);
}

Entity::~Entity(){
    for(Component* component : _currentComponents) 
        delete component;
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

// NO BORRAR
// Esto está aquí para evitar dependencia circular con GameScene
std::vector<entity_t>& 
Entity::getSceneRenderEntities() {
    return _myScene.getRenderEntities();
}