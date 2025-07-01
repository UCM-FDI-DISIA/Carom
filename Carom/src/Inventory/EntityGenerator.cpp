#include "EntityGenerator.h"
#include "GameScene.h"
#include "Inventory.h"

#include "Entity.h"
#include "PhysicsUtils.h"
#include "CircleRBComponent.h"

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
    std::ifstream f(Inventory::Instance()->pathToSavedInventory);
    json data = json::parse(f);
    std::string textureKey = "bola_blanca";
    if(data[childName]["components"][0]["atributes"]["effects"].size() >0){
        textureKey = data[childName]["components"][0]["atributes"]["effects"][0]["componentName"];
    } 

    Texture* TEX = &sdlutils().images().at(textureKey);

    if (textureKey != "bola_blanca") { //guapisimo string typing
        // Añade la textura como spritesheet 1fila 8cols, empieza en frame 0
        addComponent<RenderSpritesheetComponent>(e, &sdlutils().images().at(textureKey), 
            renderLayer::EFFECT_BALL, scale, Game::BALL_ROLLING_ROWS, Game::BALL_ROLLING_COLS, 1);

        addComponent<BallRollerAnimatorComponent>(e);
    }
    else {
        addComponent<RenderTextureComponent>(e, &sdlutils().images().at(textureKey), 
            renderLayer::EFFECT_BALL, scale);
    }

    // SCORE
    addComponent<ColorBallScorerComponent>(e);
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

entity_t EntityGenerator::generateInventoryStick(GameScene& s){

}