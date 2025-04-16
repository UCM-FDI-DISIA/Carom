#include "Component.h"
#include "Entity.h"
#include "ITransform.h"
#include "RenderTextureComponent.h"
#include "GameScene.h"
#include "CowboyPoolScene.h"
#include "ShadowComponent.h"

#include <algorithm>

using namespace std;


Entity::Entity(GameScene& scene, grpId_t gId) : _myScene(scene), _alive(true), 
    _myTransform(nullptr), _id((grp::grpId)gId) {
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

void Entity::setGameScene(GameScene* scene) {
    // TODO
    // _myScene = scene;
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

template<>
bool 
Entity::addComponent<BallEffect>(BallEffect* effectComp) {
    return internalAddComponent(effectComp->getEffectId(), effectComp);
}

bool
Entity::removeComponent(BallEffect* effectComp) {
    return internalRemoveComponent(effectComp->getEffectId());
}

bool
Entity::internalAddComponent(cmpId_t id, Component* component) {
    if(_components[id] != nullptr) return false;

    _components[id] = component;
    _currentComponents.push_back(component);
    _components[id]->init();

    return true;
}

bool
Entity::internalRemoveComponent(cmpId_t id) {
    if(_components[id] == nullptr) return false;

    auto it = find(_currentComponents.begin(), _currentComponents.end(), _components[id]);
    _currentComponents.erase(it);

    delete _components[id];

    _components[id] = nullptr;

    return true;
}

// NO BORRAR
// Esto está aquí para evitar dependencia circular con GameScene
const std::vector<entity_t>& 
Entity::getSceneRenderEntities() {
    return _myScene.getRenderEntities();
}

void 
Entity::eraseFromRenderEntities(entity_t e){
    _myScene.eraseRenderEntity(e);
}

void
Entity::addToSceneRenderEntities(entity_t e) {
    _myScene.pushToRenderEntities(e);
}