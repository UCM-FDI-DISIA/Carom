#include "EntityGenerator.h"
#include "GameScene.h"
#include "Inventory.h"

#include "Entity.h"
#include "PhysicsUtils.h"
#include "CircleRBComponent.h"
#include "RenderSpritesheetComponent.h"
#include "BallRollerAnimatorComponent.h"
#include "ColorBallScorerComponent.h"
#include "Game.h"
#include "BallHandler.h"

#include "TransformComponent.h"
#include "RenderArrayComponent.h"
#include "StickInputComponent.h"
#include "ShadowComponent.h"

#include "IdUtils.h"


entity_t EntityGenerator::generateBall(GameScene& s, std::vector<effectId_t> effects, b2Vec2 pos){
    entity_t e = new Entity(s, grp::EFFECTBALLS);

    // Scale
    float svgSize = *&sdlutils().svgs().at("positions").at("bola").width;
    float textureSize = sdlutils().images().at("bola_blanca").width(); // TODO: cambiar a textura effect ball
    float scale = svgSize/textureSize;        
    
    // RB
    float radius = PhysicsConverter::pixel2meter(static_cast<float>(*&sdlutils().svgs().at("game").at("bola_blanca").width)/2);

    e->addComponent<CircleRBComponent>(new CircleRBComponent(e, pos, b2_dynamicBody, radius));

    // RENDER
    std::string textureKey = "bola_blanca";
    if(effects.size() >0){
        textureKey = "effect_" + effects[0];
    } 

    Texture* TEX = &sdlutils().images().at(textureKey);

    if (textureKey != "bola_blanca") { //guapisimo string typing
        // Añade la textura como spritesheet 1fila 8cols, empieza en frame 0
        e->addComponent<RenderSpritesheetComponent>(new RenderSpritesheetComponent(e, &sdlutils().images().at(textureKey), 
            renderLayer::EFFECT_BALL, scale, Game::BALL_ROLLING_ROWS, Game::BALL_ROLLING_COLS, 1));

        e->addComponent<BallRollerAnimatorComponent>(new BallRollerAnimatorComponent(e));
    }
    else {
        e->addComponent<RenderTextureComponent>(new RenderTextureComponent(e, &sdlutils().images().at(textureKey), 
            renderLayer::EFFECT_BALL, scale));
    }

    // SCORE
    e->addComponent<ColorBallScorerComponent>(new ColorBallScorerComponent(e));

    //BALL HANDLER
    auto ballHandler = new BallHandler(e);
    e->addComponent<BallHandler>(ballHandler);

    for(auto effectId : effects){
        auto effect = IdUtils::getEffectFromId(effectId, ballHandler);
        ballHandler->internalAddEffect(effectId, effect, true);
    }

    return e;
}

std::vector<entity_t> EntityGenerator::generateInventoryBalls(GameScene& s, std::vector<b2Vec2> pos){
    std::vector<entity_t> res;
    int i = 0;
    for(auto slot : Inventory::Instance()->getSlotsInfo()){
        if(slot.used) res.push_back(generateBall(s, slot.ballEffects, pos[i]));
        i++;
    }
    return res;
}

entity_t EntityGenerator::generateInventoryStick(GameScene& s, b2Vec2 pos){
// LINEA DE APUNTADO
    entity_t aimline = new Entity(s, grp::AIM_LINE);
    aimline->addComponent<TransformComponent>(b2Vec2());
    aimline->addComponent<RenderArrayComponent>(&sdlutils().images().at("line"), renderLayer::STICK, 0.5, 1.0);
    
    // Scale
    float svgSize = *&sdlutils().svgs().at("game").at("palo1").width;
    float textureSize = sdlutils().images().at("palo1").width();
    float scale = svgSize/textureSize;

    entity_t e = new Entity(s, grp::PALO);
    
    e->addComponent<TransformComponent>(pos);

    e->addComponent<RenderTextureComponent>(&sdlutils().images().at("palo1"), renderLayer::STICK, scale);
    e->addComponent<TweenComponent>();
    e->addComponent<StickInputComponent>();
    e->addComponent<ShadowComponent>();

    
    e->getComponent<StickInputComponent>()->registerAimLine(aimline);
    e->getComponent<ShadowComponent>()->addShadow(b2Vec2{-0.05, -0.05}, "palo1_sombra", renderLayer::STICK_SHADOW, scale, true, true, true);
}