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
#include "Button.h"
#include "WhiteBallScorerComponent.h"

#include "IdUtils.h"


entity_t EntityGenerator::generateBall(GameScene& s, std::vector<effectId_t> effects, b2Vec2 pos, grpId_t group){
    entity_t e = new Entity(s, group);

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
    auto ballHandler = e->addComponent<BallHandler>();

    for(auto effectId : effects){
        auto effect = IdUtils::getEffectFromId(effectId, ballHandler);
        ballHandler->internalAddEffect(effectId, effect, true);
    }

    //SHADOWS

    auto shadowComp = e->addComponent<ShadowComponent>();

    //sombra de reflejo de la bola
    float a_imgScale = sdlutils().images().at("bola_cast_sombra").width();

    float a_svg_scale = sdlutils().svgs().at("game").at("bola_cast_sombra 1").width;
    float cast_scale = a_svg_scale/a_imgScale;

    shadowComp->addShadow({0,0}, "bola_cast_sombra", renderLayer::BALL_SHADOW_ON_BALL, cast_scale, true, false, true);

    //sombra de la bola
    a_imgScale = sdlutils().images().at("bola_sombra").width();
    a_svg_scale = sdlutils().svgs().at("game").at("bola_sombra 1").width;
    cast_scale = a_svg_scale/a_imgScale;

    Vector2D a_relPos{
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").x - sdlutils().svgs().at("game").at("bola_sombra 1").x - 10),
        
        PhysicsConverter::pixel2meter(sdlutils().svgs().at("game").at("bola_blanca").y - sdlutils().svgs().at("game").at("bola_sombra 1").y)
    };
    shadowComp->addShadow({a_relPos.getX(), a_relPos.getY()}, "bola_sombra", renderLayer::BALL_SHADOW_ON_TABLE, cast_scale, true, false, true);

    return e;
}

std::vector<entity_t> EntityGenerator::generateInventoryBalls(GameScene& s, std::vector<b2Vec2> pos){
    std::vector<entity_t> res;
    int i = 0;
    for(auto slot : Inventory::Instance()->getSlotsInfo()){
        if(slot.used) {
            auto ball = generateBall(s, slot.ballEffects, pos[i], grp::EFFECTBALLS);
            res.push_back(ball);

            if(slot.ballEffects.size() > 0){
                //colores
                auto color = sdlutils().inventorySlotColor[i];
                ball->getRenderer()->changeDefaultColorTint(color.r, color.g, color.b);
            }
        }
        i++;
    }
    return res;
}

entity_t EntityGenerator::generateInventoryStick(GameScene& s, b2Vec2 pos){
    auto stickID = Inventory::Instance()->getStickType();
// LINEA DE APUNTADO
    entity_t aimline = new Entity(s, grp::AIM_LINE);
    aimline->addComponent<TransformComponent>(b2Vec2());
    aimline->addComponent<RenderArrayComponent>(&sdlutils().images().at("line"), renderLayer::STICK, 0.5, 1.0);
    
    std::string textureKey = "texture_" + IdUtils::getStickStringFromId(stickID);
    // Scale
    float svgSize = *&sdlutils().svgs().at("game").at("palo1").width;
    float textureSize = sdlutils().images().at(textureKey).width();
    float scale = svgSize/textureSize;

    entity_t e = new Entity(s, grp::PALO);
    
    e->addComponent<TransformComponent>(pos);


    e->addComponent<RenderTextureComponent>(&sdlutils().images().at(textureKey), renderLayer::STICK, scale);
    e->addComponent<TweenComponent>();
    auto stickInputComp = e->addComponent<StickInputComponent>();
    auto shadowComp = e->addComponent<ShadowComponent>();
    
    stickInputComp->registerAimLine(aimline);
    std::string shadowTextureKey = "shadow_" + IdUtils::getStickStringFromId(stickID);
    shadowComp->addShadow(b2Vec2{-0.05, -0.05}, shadowTextureKey , renderLayer::STICK_SHADOW, scale, true, true, true);

    IdUtils::applyStickEffectFromId(stickID, e);

    return e;
}

entity_t EntityGenerator::generateWhiteBall(GameScene& s, b2Vec2 pos){
    auto e = generateBall(s, std::vector<effectId_t>(0), pos, grp::WHITEBALL);
    e->getRenderer()->setRenderLayer(renderLayer::WHITE_BALL);

    e->addComponent<WhiteBallScorerComponent>();

    Button::RadialButton rButton = Button::RadialButton(2.0);
    e->addComponent<Button>(rButton);
    e->getComponent<Button>()->setOnClick([e, &s](){
        for (auto& e : s.getEntitiesOfGroup(grp::PALO)) {
            e->activate();

            e->getComponent<RenderTextureComponent>()->setEnabled(false);
            e->getComponent<ShadowComponent>()->setEnabled(false);
        }
        for (auto& e : s.getEntitiesOfGroup(grp::AIM_LINE))
            e->activate();
    });
    
    s.getEntitiesOfGroup(grp::PALO)[0]->getComponent<StickInputComponent>()->registerWhiteBall(e);

    return e;
}