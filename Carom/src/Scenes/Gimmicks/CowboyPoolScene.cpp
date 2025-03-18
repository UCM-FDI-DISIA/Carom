#include "CowboyPoolScene.h"
#include "Entity.h"
#include "PhysicsUtils.h"
#include "ecs.h"

#include "TransformComponent.h"
#include "RenderTextureComponent.h"
#include "TweenComponent.h"
#include "BoxRBComponent.h"
#include "CircleRBComponent.h"
#include "ForceAreaComponent.h"
#include "FrictionComponent.h"
#include "HoleComponent.h"


namespace ecs{
    void CowboyPoolScene::initGimmick(){
        //comportamiento (anyadir entidades de arena en la mesa)
        std::cout<< "CowboyPool Gimmick Instantiated" << std::endl;
        /*
        Entity* ent = new Entity(*this, grp::DEFAULT);
        addComponent<TransformComponent>(ent, b2Vec2{0,0});
        addComponent<RenderTextureComponent>(ent, &sdlutils().images().at("bola_blanca"), renderLayer::WHITE_BALL, 1);
        addComponent<TweenComponent>(ent);

        auto a = ent->getComponent<TweenComponent>();
        a->easePosition({1,1}, 2, tween::EASE_OUT_ELASTIC,true, [=](){
            _camera->shakeCamera(0.2, 0.4);
        });
        */
        createSandBank();
        createBulletHole();
    }

    void CowboyPoolScene::createSandBank()
    {
        // SCALE
        float svgSize = *&sdlutils().svgElements_table().at("bola_blanca").width + 100;
        float textureSize = sdlutils().images().at("bola_blanca").width();
        float scale = svgSize/textureSize;

        b2Vec2 pos = PhysicsConverter::pixel2meter(
            *&sdlutils().svgElements_table().at("bola_blanca").x + 400,
            *&sdlutils().svgElements_table().at("bola_blanca").y + 50
        );

        Entity* ent = new Entity(*this, grp::DEFAULT);

        float length = PhysicsConverter::pixel2meter(svgSize/2);
        addComponent<CircleRBComponent>(ent, pos, b2_staticBody, length, true);

        addComponent<RenderTextureComponent>(ent, &sdlutils().images().at("bola_blanca"), renderLayer::GIMMICK, scale);
        ent->getComponent<RenderTextureComponent>()->changeColorTint(180, 180, 0);

        addComponent<FrictionComponent>(ent);
    }

    void CowboyPoolScene::createBulletHole(){
        // SCALE
        float svgSize = *&sdlutils().svgElements_table().at("bola_blanca").width;
        float textureSize = sdlutils().images().at("bola_blanca").width();
        float scale = svgSize/textureSize;

        b2Vec2 pos = PhysicsConverter::pixel2meter(
            *&sdlutils().svgElements_table().at("bola_blanca").x + 55,
            *&sdlutils().svgElements_table().at("bola_blanca").y
        );

        Entity* e = new Entity(*this, grp::DEFAULT);

        float radius = PhysicsConverter::pixel2meter(*&sdlutils().svgElements_table().at("bola_blanca").width/2);
        addComponent<CircleRBComponent>(e, pos, b2_staticBody, radius, true);

        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), renderLayer::POOL_HOLE, scale);
        e->getComponent<RenderTextureComponent>()->changeColorTint(0, 0, 0);

        addComponent<HoleComponent>(e, pos, 0.4f);
    }

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss): CaromScene(state, g, reward){
        if(isBoss) _boss = Boss::COWBOY_POOL;
        initGimmick();
    }

    void
    CowboyPoolScene::applyBossModifiers() {
        std::cout << "aplicando modificador de boss desde CowboyPoolScene" << std::endl;
        //TODO: intanciación tiros pistola
        _currentState->finish();
        //TODO 2: reset entities' components modified by gimmicks to original state
    }
}

