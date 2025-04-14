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
        JSONObject atributes = element->Child("atributes")->AsObject();
        if(element->Child("componentName")->AsString() == "TransformComponent"){
            transformComponent(atributes, entity);
        }
        else if(element->Child("componentName")->AsString() == "RigidBodyComponent"){
            rigidBodyComponent(atributes, entity);
        }
        else if(element->Child("componentName")->AsString() == "RenderTextureComponent"){
            renderTextureComponent(atributes, entity);
        }
        else if(element->Child("componentName")->AsString() == "BallHandler"){
            ballHandler(atributes, entity);
        }
        else if(element->Child("componentName")->AsString() == "ColorBallScorerComponent"){
            addComponent<ColorBallScorerComponent>(entity);
        }
    }
}

Entity* JsonEntityParser::createEffectBall(GameScene& gameScene, std::string file, std::string childName, b2Vec2 pos){
    //no es bueno pillar la info base de un json porque no se ajusta al SVG
    //Entity* e = Parse(gameScene, "../../resources/prefabs/basicBallPrefab.json");

    // Scale
    float svgSize = *&sdlutils().svgs().at("positions").at("bola").width;
    float textureSize = sdlutils().images().at("bola_blanca").width(); // TODO: cambiar a textura effect ball
    float scale = svgSize/textureSize;        
    
    entity_t e = new Entity(gameScene, grp::EFFECTBALLS);
    
    // RB
    float radius = PhysicsConverter::pixel2meter(static_cast<float>(*&sdlutils().svgs().at("game").at("bola_blanca").width)/2);
    addComponent<CircleRBComponent>(e, pos, b2_dynamicBody, radius);

    // RENDER
    addComponent<RenderTextureComponent>(e, &sdlutils().images().at("bola_blanca"), renderLayer::EFFECT_BALL, scale, SDL_Color{0, 150, 100, 1});

    // SCORE
    addComponent<ColorBallScorerComponent>(e);

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

void JsonEntityParser::saveBalls(std::vector<Entity*> balls) {
    for(int i = 0; i < 5; i++) {
        std::ofstream fileStream("../../resources/prefabs/inventoryData/slot" + std::to_string(i) + ".json");
        if(fileStream.is_open()) fileStream << "";
        fileStream.close();
    }

    for(int i = 0; i < balls.size(); i++) {
        Entity* currentBall = balls[i];
        std::vector<BallEffect*> ballEffects = currentBall->getComponent<BallHandler>()->getEffects();

        std::string value = "{\"components\" :[{\"componentName\" : \"BallHandler\",\"atributes\" : {\"effects\": [";
        
        for(int i = 0; i < ballEffects.size(); i++) {
            BallEffect* effect = ballEffects[i];

            value += "{\"componentName\" : ";
            if (dynamic_cast<AbacusEffect*>(effect) != nullptr) value += "\"AbacusEffect\"";
            else if (dynamic_cast<BowlingEffect*>(effect) != nullptr) value += "\"BowlingEffect\"";
            else if (dynamic_cast<X2Effect*>(effect) != nullptr) value += "\"X2Effect\"";
            else if (dynamic_cast<QuanticEffect*>(effect) != nullptr) value += "\"QuanticEffect\"";
            else if (dynamic_cast<PokeballEffect*>(effect) != nullptr) value += "\"PokeballEffect\"";
            else if (dynamic_cast<CristalEffect*>(effect) != nullptr) value += "\"CristalEffect\"";
            else if (dynamic_cast<PetanqueEffect*>(effect) != nullptr) value += "\"PetanqueEffect\"";
            value += "}";

            if(i != ballEffects.size() - 1) value += ", ";
        }

        value += "]}}]}";

        std::ofstream fileStream("../../resources/prefabs/inventoryData/slot" + std::to_string(i) + ".json");
        if(fileStream.is_open()) fileStream << value;
        fileStream.close();
    }

}


