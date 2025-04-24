#include "JsonEntityParser.h"
#include "JSON.h"
#include "Vector2D.h"
#include "SDLUtils.h"

#include "TransformComponent.h"

#include "BoxRBComponent.h"
#include "CapsuleRBComponent.h"
#include "CircleRBComponent.h"
#include "PolygonRBComponent.h"
#include "RectangleRBComponent.h"
#include "PhysicsUtils.h"

#include "BallHandler.h"
#include "BowlingEffect.h"
#include "CristalEffect.h"
#include "AbacusEffect.h"
#include "PetanqueEffect.h"
#include "PokeballEffect.h"
#include "QuanticEffect.h"
#include "X2Effect.h"

#include "RenderTextureComponent.h"
#include "Texture.h"

#include "ColorBallScorerComponent.h"
#include "ColorBallScorerComponent.h"

#include "DonutStickEffect.h"
#include "MagicWandStickEffect.h"
#include "BoxingGloveStickEffect.h"
#include "GranadeLauncherStickEffect.h"
#include "StickInputComponent.h"
#include "InventoryManager.h"

#include "ShadowComponent.h"

#include <iostream>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>

Entity* JsonEntityParser::Parse(GameScene& gameScene,std::string file, std::string childName){
    JSONValue* entityElements = JSON::ParseFromFile(file);
    
    Entity* entity = new Entity(gameScene, (grp::grpId) entityElements->Child("ID")->AsNumber());
    AddComponentsFromJSON(entity, file, childName);
    
    return entity;
}

void JsonEntityParser::AddComponentsFromJSON(Entity* entity, std::string JSONfile, std::string childName){
    JSONValue* entityElements = JSON::ParseFromFile(JSONfile);

    JSONArray componentArray;

    if(childName == "NONE") componentArray = entityElements->Child("components")->AsArray();
    else componentArray = entityElements->Child(childName.c_str())->Child("components")->AsArray();

    for(auto element : componentArray){
        JSONObject atributes;
        if(element->HasChild("atributes")) atributes = element->Child("atributes")->AsObject();
        std::string componentName = element->Child("componentName")->AsString();

        if(componentName == "TransformComponent"){
            transformComponent(atributes, entity);
        }
        else if(componentName == "RigidBodyComponent"){
            rigidBodyComponent(atributes, entity);
        }
        else if(componentName == "RenderTextureComponent"){
            renderTextureComponent(atributes, entity);
        }
        else if(componentName == "BallHandler"){
            ballHandler(atributes, entity);
        }
        else if(componentName == "ColorBallScorerComponent"){
            addComponent<ColorBallScorerComponent>(entity);
        }
        else if (componentName == "StickInputComponent"){
            stickInputComponent(entity);
        }
        else if (componentName == "DonutStickEffect"){
            donutStickEffect(atributes,entity);
        }
        else if (componentName == "MagicWandStickEffect"){
            magicWandStickEffect(atributes,entity);
        }
        else if (componentName =="BoxingGloveStickEffect"){
            boxingGloveStickEffect(atributes,entity);
        }
        else if (componentName == "GrenadeLauncherStickEffect"){
            grenadeLauncherStickEffect(atributes,entity);
        }
    }
}

Entity* JsonEntityParser::createEffectBall(GameScene& gameScene, std::string file, std::string childName, b2Vec2 pos){
    //si en el svg no existe slotX, devuelve nullptr
    if(!JSON::ParseFromFile(file)->HasChild(childName.c_str())) return nullptr;
    // Scale
    float svgSize = *&sdlutils().svgs().at("positions").at("bola").width;
    float textureSize = sdlutils().images().at("bola_blanca").width(); // TODO: cambiar a textura effect ball
    float scale = svgSize/textureSize;        
    
    entity_t e = new Entity(gameScene, grp::EFFECTBALLS);
    
    // RB
    float radius = PhysicsConverter::pixel2meter(static_cast<float>(*&sdlutils().svgs().at("game").at("bola_blanca").width)/2);
    addComponent<CircleRBComponent>(e, pos, b2_dynamicBody, radius);

    // RENDER
    std::ifstream f(InventoryManager::Instance()->pathToInventory);
    json data = json::parse(f);
    std::string textureKey = "bola_blanca";
    if(data[childName]["components"][0]["atributes"]["effects"].size() >0){
        textureKey = data[childName]["components"][0]["atributes"]["effects"][0]["componentName"];
    } 

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at(textureKey), renderLayer::EFFECT_BALL, scale);

    // SCORE
    addComponent<ColorBallScorerComponent>(e);

    AddComponentsFromJSON(e, file, childName);
    return e;
}

Entity* JsonEntityParser::createStick(GameScene& gameScene, std::string file, std::string childName, b2Vec2 pos){
    // Scale
    float svgSize = *&sdlutils().svgs().at("game").at("palo1").width;
    float textureSize = sdlutils().images().at("palo1").width();
    float scale = svgSize/textureSize;

    entity_t e = new Entity(gameScene, grp::PALO);
    
    addComponent<TransformComponent>(e, pos);

    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("palo1"), renderLayer::STICK, scale);
    addComponent<TweenComponent>(e);
    addComponent<StickInputComponent>(e);
    addComponent<ShadowComponent>(e);

    e->getComponent<ShadowComponent>()->addShadow(b2Vec2{-0.05, -0.05}, "palo1_sombra", renderLayer::STICK_SHADOW, scale, true, true, true);

    AddComponentsFromJSON(e, file, childName);

    return e;
}

void JsonEntityParser::transformComponent(const JSONObject& atributes, Entity* entity){
    b2Vec2 position(atributes.at("x")->AsNumber(), atributes.at("y")->AsNumber());
    addComponent<TransformComponent>(entity, position);
}

void JsonEntityParser::rigidBodyComponent(const JSONObject& atributes, Entity* entity){
    //escoge el tipo de body type
    b2BodyType bodyType;
    if(atributes.at("b2BodyType")->AsString() == "static") bodyType = b2_staticBody;
    else if(atributes.at("b2BodyType")->AsString() == "kinematic") bodyType = b2_kinematicBody;
    else if(atributes.at("b2BodyType")->AsString() == "dynamic") bodyType = b2_dynamicBody;

    //asigna la posicion
    b2Vec2 pos(atributes.at("pos")->Child("x")->AsNumber(), atributes.at("pos")->Child("y")->AsNumber());
    
    float density = atributes.at("density")->AsNumber(),
            friction = atributes.at("friction")->AsNumber(),
            restitution = atributes.at("restitution")->AsNumber();
    //escoge la forma del rigidbody
    if(atributes.contains("CircleShape")){
        float radius = atributes.at("CircleShape")->Child("radius")->AsNumber();//accede al radio del circulo
        
        addComponent<CircleRBComponent>(entity, pos, bodyType, radius, false, b2Rot(1.0f, 0.0f), density, friction, restitution);
    }
    else if (atributes.contains("CapsuleShape")){
        JSONValue* capsule = atributes.at("CapsuleShape");
        float with = capsule->Child("with")->AsNumber(),
                height = capsule->Child("height")->AsNumber();
        addComponent<CapsuleRBComponent>(entity, pos, bodyType, with, height, false, b2Rot(1.0f, 0.0f), density, friction, restitution);
    }
    else if (atributes.contains("PolygonShape")){//esto falla
        JSONValue* poligon = atributes.at("PolygonShape");
        int size = poligon->Child("size")->AsNumber();
        float temp1=0, temp2=0;
        std::vector<b2Vec2> vertex(size);
        for(int i = 0; i < size; i++){
            temp1 = poligon->Child("vertex")->AsArray()[i]->Child("x")->AsNumber();
            temp2 = poligon->Child("vertex")->AsArray()[i]->Child("y")->AsNumber();
            vertex[i] = {temp1, temp2};
        }
        if(poligon->HasChild("radius")){
            float radius = poligon->Child("radius")->AsNumber();
            addComponent<PolygonRBComponent>(entity, pos, bodyType, vertex, radius, false, b2Rot(1.0f, 0.0f), density, friction, restitution);
        }
        else 
            addComponent<PolygonRBComponent>(entity, pos, bodyType, vertex, 0.0f, false, b2Rot(1.0f, 0.0f), density, friction, restitution);
    }
    else if(atributes.contains("RectangleShape")){
        float with = atributes.at("RectangleShape")->Child("with")->AsNumber(),
                height = atributes.at("RectangleShape")->Child("height")->AsNumber();
        addComponent<RectangleRBComponent>(entity, pos, bodyType, with, height, false, b2Rot(1.0f, 0.0f), density, friction, restitution);
    }
    else if(atributes.contains("SquareShape")){
        float side = atributes.at("SquareShape")->Child("side")->AsNumber();
        addComponent<BoxRBComponent>(entity, pos, bodyType, side, false, b2Rot(1.0f, 0.0f), density, friction, restitution);
    }
}

void JsonEntityParser::renderTextureComponent(const JSONObject& atributes, Entity* entity){
    std::string key = atributes.at("textureID")->AsString();       
    std::cout<<key;
    float scale = atributes.at("scale")->AsNumber();

    int layer = atributes.at("layer")->AsNumber();
    
    addComponent<RenderTextureComponent>(entity, &sdlutils().images().at(key), layer, scale, SDL_Color{0, 150, 100, 1});
}

void JsonEntityParser::ballHandler(const JSONObject& atributes, Entity* entity){
    addComponent<BallHandler>(entity);
    for(auto element : atributes.at("effects")->AsArray()){
        if(element->Child("componentName")->AsString() == "BowlingEffect") 
            addComponent<BowlingEffect>(entity); 
        else if(element->Child("componentName")->AsString() == "X2Effect")
            addComponent<X2Effect>(entity);
        else if(element->Child("componentName")->AsString() == "AbacusEffect")
            addComponent<AbacusEffect>(entity);
        else if(element->Child("componentName")->AsString() == "CristalEffect")
            addComponent<CristalEffect>(entity);
        else if(element->Child("componentName")->AsString() == "PetanqueEffect")
            addComponent<PetanqueEffect>(entity);
        else if(element->Child("componentName")->AsString() == "PokeballEffect")
            addComponent<PokeballEffect>(entity);
        else if(element->Child("componentName")->AsString() == "QuanticEffect")
            addComponent<QuanticEffect>(entity);
    }
}

std::vector<std::string> JsonEntityParser::getBallEffects(entity_t ball){
    std::vector<std::string> res;
    std::vector<BallEffect*> ballEffects = ball->getComponent<BallHandler>()->getEffects();

    for(int i = 0; i < ballEffects.size(); i++) {
        BallEffect* effect = ballEffects[i];
        if (dynamic_cast<AbacusEffect*>(effect) != nullptr) res.push_back ("AbacusEffect");
        else if (dynamic_cast<BowlingEffect*>(effect) != nullptr) res.push_back("BowlingEffect");
        else if (dynamic_cast<X2Effect*>(effect) != nullptr) res.push_back("X2Effect");
        else if (dynamic_cast<QuanticEffect*>(effect) != nullptr) res.push_back("QuanticEffect");
        else if (dynamic_cast<PokeballEffect*>(effect) != nullptr) res.push_back("PokeballEffect");
        else if (dynamic_cast<CristalEffect*>(effect) != nullptr) res.push_back("CristalEffect");
        else if (dynamic_cast<PetanqueEffect*>(effect) != nullptr) res.push_back("PetanqueEffect");
    }

    return res;

};

void JsonEntityParser::stickInputComponent(Entity* e){
    addComponent<StickInputComponent>(e);
}
void JsonEntityParser::donutStickEffect(const JSONObject& atributes,Entity* e){
    addComponent<DonutStickEffect>(e);
    auto renderTexture = e->getComponent<RenderTextureComponent>();
    renderTexture->setTexture(&sdlutils().images().at("donut"));

    auto shadowComponent = e->getComponent<ShadowComponent>();
    shadowComponent->getShadows().clear();
    shadowComponent->addShadow(b2Vec2{-0.05, -0.05}, "donut_sombra", renderLayer::STICK_SHADOW, renderTexture->getScale(), true, true, true);
}
void JsonEntityParser::magicWandStickEffect(const JSONObject& atributes,Entity* e){
    addComponent<MagicWandStickEffect>(e);
    auto renderTexture = e->getComponent<RenderTextureComponent>();
    renderTexture->setTexture(&sdlutils().images().at("magic_wand"));

    auto shadowComponent = e->getComponent<ShadowComponent>();
    shadowComponent->getShadows().clear();
    shadowComponent->addShadow(b2Vec2{-0.05, -0.05}, "magic_wand_shadow", renderLayer::STICK_SHADOW, renderTexture->getScale(), true, true, true);
}
void JsonEntityParser::boxingGloveStickEffect(const JSONObject& atributes, Entity* e){
    addComponent<BoxingGloveStickEffect>(e, atributes.at("factor")->AsNumber());
}
void JsonEntityParser::grenadeLauncherStickEffect(const JSONObject& atributes, Entity* e){
    addComponent<GranadeLauncherStickEffect>(e, atributes.at("radius")->AsNumber(), atributes.at("explosionForce")->AsNumber(), atributes.at("explosionDelay")->AsNumber());

    auto renderTexture = e->getComponent<RenderTextureComponent>();
    renderTexture->setTexture(&sdlutils().images().at("lanzagranadas"));
    auto shadowComponent = e->getComponent<ShadowComponent>();
    shadowComponent->getShadows().clear();
    shadowComponent->addShadow(b2Vec2{-0.05, -0.05}, "lanzagranadas_sombra", renderLayer::STICK_SHADOW, renderTexture->getScale(), true, true, true);
}