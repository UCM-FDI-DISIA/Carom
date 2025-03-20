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
#include "RNG_Manager.h"
#include "RandomItem.h"


namespace ecs{

    CowboyPoolScene::CowboyPoolScene(State* state, Game* g, GameScene* reward, bool isBoss): CaromScene(state, g, reward){
        if(isBoss) _boss = Boss::COWBOY_POOL;
        initGimmick();
    }

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
        createBulletHoles(3); // TODO: numero de agujeros random?
    }

    void CowboyPoolScene::createSandBank()
    {
        // SCALE
        float svgSize = *&sdlutils().svgs().at("game").at("bola_blanca").width + 100;
        float textureSize = sdlutils().images().at("bola_blanca").width();
        float scale = svgSize/textureSize;

        b2Vec2 pos = PhysicsConverter::pixel2meter(
            *&sdlutils().svgs().at("game").at("bola_blanca").x + 400,
            *&sdlutils().svgs().at("game").at("bola_blanca").y + 50
        );

        Entity* ent = new Entity(*this, grp::GIMMICK);

        float length = PhysicsConverter::pixel2meter(svgSize/2);
        addComponent<CircleRBComponent>(ent, pos, b2_staticBody, length, true);

        addComponent<RenderTextureComponent>(ent, &sdlutils().images().at("bola_blanca"), renderLayer::GIMMICK, scale);
        ent->getComponent<RenderTextureComponent>()->changeColorTint(180, 180, 0);

        addComponent<FrictionComponent>(ent);
    }

    void CowboyPoolScene::createBulletHole(const b2Vec2& pos){
        // SCALE
        float svgSize = *&sdlutils().svgs().at("game").at("hole1").width;
        float textureSize = sdlutils().images().at("hole").width();
        float scale = svgSize/textureSize;

        Entity* e = new Entity(*this, grp::BOSS_MODIFIERS);

        float radius = PhysicsConverter::pixel2meter(svgSize/2);
        addComponent<CircleRBComponent>(e, pos, b2_staticBody, radius, true);

        addComponent<RenderTextureComponent>(e, &sdlutils().images().at("hole"), renderLayer::POOL_HOLE, scale);

        addComponent<HoleComponent>(e, 0.4f);
    }

    void 
    CowboyPoolScene::createBulletHoles(int n) {
        int npos = sdlutils().svgs().at("shot_positions").size();
        assert(n <= npos);

        std::vector<RandomItem<int>> positions;
        for(int i = 1; i <= npos; ++i)
            positions.push_back(RandomItem(i, 1.0f));
        
        
        while(n > 0 && positions.size() > 0) {
            // Obtener posición aleatoria para el agujero
            int id = _rngManager->getRandomItem(positions, true) ;

            std::string s = "shot_hole";
            if(id > 1)
                s += ("_" + std::to_string(id));
            
            auto& hole = sdlutils().svgs().at("shot_positions").at(s);
            b2Vec2 hole_pos = PhysicsConverter::pixel2meter(hole.x, hole.y);
            float hole_radius = sdlutils().svgs().at("shot_positions").at("shot_hole").width/2;

            // Comprobar si es válido
            bool valid = true;

            auto& balls = (getEntitiesOfGroup(ecs::grp::WHITEBALL));
            for(auto& e : balls) {
                if(e->tryGetComponent<CircleRBComponent>()) { // TODO: cambiar esto cuando se mergee con la rama de Diego el tryGetComponent
                    if(!canPlaceHole(e, hole_pos, hole_radius)) {
                        valid = false;
                        break;
                    }
                }
            }
            
            if(!valid) continue; // No seguir comprobando si no es válido

            balls = getEntitiesOfGroup(ecs::grp::EFFECTBALLS);
            for(auto& e : balls) {
                if(e->tryGetComponent<CircleRBComponent>()) { // TODO: cambiar esto cuando se mergee con la rama de Diego el tryGetComponent
                    if(!canPlaceHole(e, hole_pos, hole_radius)) {
                        valid = false;
                        break;
                    }
                }
            }
            
            // Si la posición es válida, crear agujero
            if(valid) {
                createBulletHole(hole_pos);
                --n;
            }

        }
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

        //TODO 2: reset entities' components modified by gimmicks to original state
        _currentState->finish();
    }

    void 
    CowboyPoolScene::clearBossModifiers()
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

    void CowboyPoolScene::animateBossHand(){
        
    }



    bool
    CowboyPoolScene::canPlaceHole(entity_t e, b2Vec2 hole_pos, float hole_radius) {
        auto ball_tr = e->getComponent<CircleRBComponent>();
        auto ball_pos = ball_tr->getPosition();
        auto ball_radius = PhysicsConverter::pixel2meter(ball_tr->getRadius());
        
        return !PhysicsConverter::circleOverlap(hole_pos, hole_radius, ball_pos, ball_radius);
    }
}

