#include <SDLUtils.h>
#include <algorithm>
#include "RenderTextureComponent.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "RectangleRBComponent.h"

#include "GameScene.h"
#include "../Game.h"
#include "Camera.h"

GameScene::GameScene(Game* game): game(game), _worldCamera(0,0), _UICamera(0,0){ }

GameScene::~GameScene(){};

// TODO: componentes Transform físico y normal
// Creates a table composed by 3 entities for textures and 4 entities that are the colliders of each side of the table.
// The table is not an entity per se, is represented by a group of entities.
// Those entities are grouped here -> _entsByGroup[grp::TABLE]
void
GameScene::createTable(){

    // !---- TEXTURES ----//
    // Set scale (same for all)
    float svgSize = *&sdlutils().svgElements_table().at("mesa_marco").width;
    float textureSize = sdlutils().images().at("mesa1").width();
    float scale = svgSize/textureSize;

    // Entidad marco
    entity_t e_marco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_m = PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("mesa_marco").x, *&sdlutils().svgElements_table().at("mesa_marco").y);
    addComponent<TransformComponent>(e_marco, pos_m);
    addComponent<RenderTextureComponent>(e_marco, &sdlutils().images().at("mesa1"), 3, scale);

    // Entidad suelo
    entity_t e_fondo = new Entity(*this, grp::TABLE);
    b2Vec2 pos_f = PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("fondo_mesa").x, *&sdlutils().svgElements_table().at("fondo_mesa").y);
    addComponent<TransformComponent>(e_fondo, pos_f);
    addComponent<RenderTextureComponent>(e_fondo, &sdlutils().images().at("fondo"), 1, scale);

    // Entidad sombraMarco
    entity_t e_sombraMarco = new Entity(*this, grp::TABLE);
    b2Vec2 pos_s = PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("mesa_sombra").x, *&sdlutils().svgElements_table().at("mesa_sombra").y);
    addComponent<TransformComponent>(e_sombraMarco, b2Vec2{pos_s.x - 0.2f, pos_s.y - 0.2f});
    addComponent<RenderTextureComponent>(e_sombraMarco, &sdlutils().images().at("mesa1_sombra"), 0, scale);

    // !---- BODIES ----//
    // Left cushion coll
    entity_t e_coll_left = new Entity(*this, grp::TABLE);
    b2Vec2 pos_coll_left = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements_table().at("left_cushion_coll").x,
        *&sdlutils().svgElements_table().at("left_cushion_coll").y
    );

    addComponent<RectangleRBComponent>(e_coll_left, pos_coll_left, b2_staticBody, 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("left_cushion_coll").width), 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("left_cushion_coll").height));

    // Right cushion coll
    entity_t e_coll_right = new Entity(*this, grp::TABLE);
    b2Vec2 pos_coll_right = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements_table().at("right_cushion_coll").x,
        *&sdlutils().svgElements_table().at("right_cushion_coll").y
    );

    addComponent<RectangleRBComponent>(e_coll_right, pos_coll_right, b2_staticBody, 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("right_cushion_coll").width), 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("right_cushion_coll").height));

    // Top cushion coll
    entity_t e_coll_top = new Entity(*this, grp::TABLE);
    b2Vec2 pos_coll_top = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements_table().at("top_cushion_coll").x,
        *&sdlutils().svgElements_table().at("top_cushion_coll").y
    );

    addComponent<RectangleRBComponent>(e_coll_top, pos_coll_top, b2_staticBody, 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("top_cushion_coll").width), 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("top_cushion_coll").height));

    // Bottom cushion coll
    entity_t e_coll_bottom = new Entity(*this, grp::TABLE);
    b2Vec2 pos_coll_bottom = PhysicsConverter::pixel2meter(
        *&sdlutils().svgElements_table().at("bottom_cushion_coll").x,
        *&sdlutils().svgElements_table().at("bottom_cushion_coll").y
    );

    addComponent<RectangleRBComponent>(e_coll_bottom, pos_coll_bottom, b2_staticBody, 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("bottom_cushion_coll").width), 
        PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("bottom_cushion_coll").height));
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

void GameScene::createBackground(std::string key){
    //sprite de suelo
    Entity* a_suelo = new Entity(*this, grp::BACKGROUND);
    addComponent<TransformComponent>(a_suelo, b2Vec2{0,0});
    addComponent<RenderTextureComponent>(a_suelo, &sdlutils().images().at(key), -1, 1);
}