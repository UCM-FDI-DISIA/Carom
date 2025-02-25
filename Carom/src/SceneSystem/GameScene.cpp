#include <SDLUtils.h>
#include <algorithm>
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"

#include "GameScene.h"
#include "../Game.h"
#include "Camera.h"

namespace ecs{

GameScene::GameScene(Game* game): game(game), _worldCamera(0,0), _UICamera(0,0){ }

GameScene::~GameScene(){};

// TODO: componentes Transform físico y normal
// Creates a table composed by 3 entities for textures and 4 entities that are the colliders of each side of the table.
// The table is not an entity per se, is represented by a group of entities.
// Those entities are grouped here -> _entsByGroup[grp::TABLE]
void
GameScene::createTable(){
    
    // Entidad marco
    entity_t e_marco = new Entity(*this);
    b2Vec2 pos_m = PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("mesa_marco").x, *&sdlutils().svgElements().at("mesa_marco").y);
    
    addComponent<TransformComponent>(e_marco, pos_m);
    e_marco->getComponent<TransformComponent>()->setScale({0.85f, 0.85f});
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e_marco);
    addComponent<RenderTextureComponent>(e_marco, &sdlutils().images().at("marco2"), 2);
    _entsByGroup[grp::TABLE].push_back(e_marco);
    _entities.push_back(e_marco);

    // Entidad suelo
    entity_t e_fondo = new Entity(*this);
    b2Vec2 pos_f = PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("fondo_mesa").x, *&sdlutils().svgElements().at("fondo_mesa").y);
    addComponent<TransformComponent>(e_fondo, pos_f);
    e_fondo->getComponent<TransformComponent>()->setScale({0.85f, 0.85f});
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e_fondo);
    addComponent<RenderTextureComponent>(e_fondo, &sdlutils().images().at("fondo"), 1);
    _entsByGroup[grp::TABLE].push_back(e_fondo);
    _entities.push_back(e_fondo);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this);
    b2Vec2 pos_s = PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("mesa_sombra").x, *&sdlutils().svgElements().at("mesa_sombra").y);
    addComponent<TransformComponent>(e_sombraMarco, pos_s);
    e_sombraMarco->getComponent<TransformComponent>()->setScale({0.85f, 0.85f});
    // Must be pushed back into renderable vector before adding the component for proper sort!
    _entsRenderable.push_back(e_sombraMarco);
    addComponent<RenderTextureComponent>(e_sombraMarco, &sdlutils().images().at("mesa1_sombra"), 0);
    _entsByGroup[grp::TABLE].push_back(e_sombraMarco);
    _entities.push_back(e_sombraMarco);

    //---- BODIES ----//
    // Create an entity for each cushion (border) of the table
    // for (int i = 0; i < game->nCushions; ++i){
    //     entity_t e_coll = new Entity(*this);
    //     b2Vec2 pos_coll = {};
    //     addComponent<TransformComponent>(e_coll, pos_coll); // TODO: cambiar a transform físico
    //     _entsByGroup[grp::TABLE].push_back(e_coll);
    //     _entities.push_back(e_coll);
    // }

    // Left cushion coll
    entity_t e_coll = new Entity(*this);
    b2Vec2 pos_coll = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements().at("left_cushion_coll").x,
        *&sdlutils().svgElements().at("left_cushion_coll").y
    );
    ecs::PolygonShape *ps = new ecs::PolygonShape(
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("left_cushion_coll").width/2),
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("left_cushion_coll").height/2)
    );
    addComponent<RigidBodyComponent>(e_coll, pos_coll, b2_staticBody, ps);
    _entsByGroup[grp::TABLE].push_back(e_coll);
    _entities.push_back(e_coll);

    // Right cushion coll
    entity_t e_coll_right = new Entity(*this);
    b2Vec2 pos_coll_right = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements().at("right_cushion_coll").x,
        *&sdlutils().svgElements().at("right_cushion_coll").y
    );
    ecs::PolygonShape *ps_right = new ecs::PolygonShape(
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("right_cushion_coll").width/2),
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("right_cushion_coll").height/2)
    );
    addComponent<RigidBodyComponent>(e_coll_right, pos_coll_right, b2_staticBody, ps_right);
    _entsByGroup[grp::TABLE].push_back(e_coll_right);
    _entities.push_back(e_coll_right);

    // Top cushion coll
    entity_t e_coll_top = new Entity(*this);
    b2Vec2 pos_coll_top = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements().at("top_cushion_coll").x,
        *&sdlutils().svgElements().at("top_cushion_coll").y
    );
    ecs::PolygonShape *ps_top = new ecs::PolygonShape(
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("top_cushion_coll").width/2),
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("top_cushion_coll").height/2)
    );
    addComponent<RigidBodyComponent>(e_coll_top, pos_coll_top, b2_staticBody, ps_top);
    _entsByGroup[grp::TABLE].push_back(e_coll_top);
    _entities.push_back(e_coll_top);

    // Bottom cushion coll
    entity_t e_coll_bottom = new Entity(*this);
    b2Vec2 pos_coll_bottom = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements().at("bottom_cushion_coll").x,
        *&sdlutils().svgElements().at("bottom_cushion_coll").y
    );
    ecs::PolygonShape *ps_bottom = new ecs::PolygonShape(
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("bottom_cushion_coll").width/2),
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements().at("bottom_cushion_coll").height/2)
    );
    addComponent<RigidBodyComponent>(e_coll_bottom, pos_coll_bottom, b2_staticBody, ps_bottom);
    _entsByGroup[grp::TABLE].push_back(e_coll_bottom);
    _entities.push_back(e_coll_bottom);

}

void GameScene::sortRenderOrder(){
    std::sort(_entsRenderable.begin(), _entsRenderable.end(), [](entity_t a, entity_t b) {
        return a->getComponent<RenderTextureComponent>()->renderOrder < b->getComponent<RenderTextureComponent>()->renderOrder;
    });
}

void GameScene::render(){
    for (auto entity : _entsRenderable) {
        entity->render(&_worldCamera);
    }
}

void GameScene::update(){
    for (Entity* entity : _entities) {
        entity->update();
    }
}

void GameScene::handleEvent(){
    for (auto entity : _entities) {
        entity->handleEvents();
    }
}

void GameScene::clear(){
     for (auto entity : _entities) {
        delete entity;
    }
}

Camera* GameScene::getWorldCamera(){
    return &_worldCamera;
}

Camera* GameScene::getUICamera() {
    return &_UICamera;
}

void GameScene::setWorldCamera(b2Vec2 pos){
    _worldCamera = Camera(pos.x, pos.y);
}

void GameScene::setUICamera(b2Vec2 pos){
    _UICamera = Camera(pos.x, pos.y);
}
};

