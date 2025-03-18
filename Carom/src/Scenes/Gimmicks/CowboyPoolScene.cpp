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
        Entity* boss = new Entity(*this, grp::BOSS_HAND);
        addComponent<TransformComponent>(boss, b2Vec2{0,.5f});
        addComponent<RenderTextureComponent>(boss, &sdlutils().images().at("cowboy_hand"), renderLayer::BOSS_HAND, .3f);
        addComponent<TweenComponent>(boss);
        getComponent<TweenComponent>(boss)->easePosition({.5f, .5f}, 2, tween::EASE_IN_OUT_CUBIC, true);
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

        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);
        //e->getComponent<RenderTextureComponent>()->changeColorTint(0, 0, 0);

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

