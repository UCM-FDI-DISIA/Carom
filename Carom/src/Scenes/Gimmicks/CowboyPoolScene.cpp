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

        Entity* ent = new Entity(*this, grp::BOSS_MODIFIERS);

        float length = PhysicsConverter::pixel2meter(svgSize/2);
        addComponent<CircleRBComponent>(ent, pos, b2_staticBody, length, true);

        addComponent<RenderTextureComponent>(ent, &sdlutils().images().at("bola_blanca"), renderLayer::GIMMICK, scale);
        ent->getComponent<RenderTextureComponent>()->changeColorTint(180, 180, 0);

        addComponent<FrictionComponent>(ent);
    }

    void CowboyPoolScene::createBulletHole(){
        // SCALE
        float svgSize = *&sdlutils().svgElements_table().at("hole1").width;
        float textureSize = sdlutils().images().at("hole").width();
        float scale = svgSize/textureSize;

        b2Vec2 pos = PhysicsConverter::pixel2meter(
            *&sdlutils().svgElements_table().at("hole1").x + 70,
            *&sdlutils().svgElements_table().at("hole1").y
        );

        Entity* e = new Entity(*this, grp::BOSS_MODIFIERS);

        float radius = PhysicsConverter::pixel2meter(svgSize/2);
        addComponent<CircleRBComponent>(e, pos, b2_staticBody, radius, true);

        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

        addComponent<HoleComponent>(e, 0.4f);
    }

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss): CaromScene(state, g, reward){
        if(isBoss) _boss = Boss::COWBOY_POOL;
        initGimmick();
    }

    void
    CowboyPoolScene::applyBossModifiers() {
        std::cout << "aplicando modificador de boss desde CowboyPoolScene" << std::endl;
        //TODO: intanciación tiros pistola
        for(auto& e: getEntitiesOfGroup(ecs::grp::BOSS_MODIFIERS)){
            if (e->tryGetComponent<HoleComponent>()){
                auto hole = e->getComponent<HoleComponent>();
                hole->resetHole(b2Vec2_zero); // TODO: definir posición
                e->activate();
                // std::cout << "apply boss modifiers" << std::endl;
            }
        }

        _currentState->finish();
        //TODO 2: reset entities' components modified by gimmicks to original state

    }
    void CowboyPoolScene::clearBossModifiers()
    {
        // Reset hole changes on balls and deactivate it
        for(auto& e: getEntitiesOfGroup(ecs::grp::BOSS_MODIFIERS)){
            if (e->tryGetComponent<HoleComponent>()){
                auto hole = e->getComponent<HoleComponent>();
                hole->resetChanges();
                e->deactivate();
                // std::cout << "reset changes clear boss" << std::endl;
            }
        }
    }
}
