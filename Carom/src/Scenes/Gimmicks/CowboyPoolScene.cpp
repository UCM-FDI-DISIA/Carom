#include "CowboyPoolScene.h"
#include "Entity.h"
#include "ecs.h"
#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "TweenComponent.h"

namespace ecs{
    void CowboyPoolScene::initGimmick(){
        //comportamiento (anyadir entidades de arena en la mesa)
        std::cout<< "CowboyPool Gimmick Instantiated" << std::endl;

        Entity* ent = new Entity(*this, grp::DEFAULT);
        addComponent<TransformComponent>(ent, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ent, &sdlutils().images().at("bola_blanca"), 1000, 1);
        addComponent<TweenComponent>(ent);

        auto a = ent->getComponent<TweenComponent>();
        a->easePosition({1,1}, 2, tween::EASE_OUT_ELASTIC,true, [=](){
            _camera->shakeCamera(0.2, 0.4);
        });

        
    }

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward): CaromScene(state, g, reward){
        initGimmick();
    }
}

