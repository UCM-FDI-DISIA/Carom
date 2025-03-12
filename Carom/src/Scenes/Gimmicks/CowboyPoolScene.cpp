#include "CowboyPoolScene.h"
#include "Entity.h"
#include "ecs.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"

namespace ecs{
    void CowboyPoolScene::initGimmick(){
        //comportamiento (anyadir entidades de arena en la mesa)
        std::cout<< "CowboyPool Gimmick Instantiated" << std::endl;

        Entity* ent = new Entity(*this, grp::DEFAULT);
        addComponent<TransformComponent>(ent, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ent, &sdlutils().images().at("bola_blanca"), 1000, 1);

        auto tr = getComponent<TransformComponent>(ent);

        _tweenManager->easePosition(tr, {10, 0}, 3, tween::EASE_IN_BACK);
    }

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward): CaromScene(state, g, reward){
        initGimmick();
    }
}

