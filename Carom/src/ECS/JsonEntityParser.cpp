#include "JsonEntityParser.h"
#include "JSON.h"
#include "Vector2D.h"

#include "TransformComponent.h"

#include "BoxRBComponent.h"
#include "CapsuleRBComponent.h"
#include "CircleRBComponent.h"
#include "PolygonRBComponent.h"
#include "RectangleRBComponent.h"

#include "RenderTextureComponent.h"
#include "Texture.h"

#include <iostream>
#include <vector>

namespace ecs
{
    Entity* JsonEntityParser::Parse(GameScene& gameScene,std::string file){

        JSONValue* entityElements = JSON::ParseFromFile(file);
        Entity* entity = new Entity(gameScene, (ecs::grp::grpId) entityElements->Child("ID")->AsNumber());
        //std::cout<<JSON::Stringify(entityElements);
    
        for(auto element : entityElements->Child("components")->AsArray()){
            if(element->Child("componentName")->AsString() == "TransformComponent"){
                JSONObject atributes = element->Child("atributes")->AsObject();
                transformComponent(atributes, entity);
            }
            else if(element->Child("componentName")->AsString() == "RigidBodyComponent"){
                JSONObject atributes = element->Child("atributes")->AsObject();
                rigidBodyComponent(atributes, entity);
            }
            else if(element->Child("componentName")->AsString() == "RenderTextureComponent"){
                JSONObject atributes = element->Child("atributes")->AsObject();
                renderTextureComponent(atributes, entity);
            }
        }
       return nullptr;
    }
    
    void JsonEntityParser::transformComponent(const JSONObject& atributes, Entity* entity){
        b2Vec2 position(atributes.at("x")->AsNumber(), atributes.at("y")->AsNumber());
        addComponent<ecs::TransformComponent>(entity, position);
    }

    void JsonEntityParser::rigidBodyComponent(const JSONObject& atributes, Entity* entity){
        //escoge el tipo de body type
        b2BodyType bodyType;
        if(atributes.at("b2BodyType")->AsString() == "static") bodyType = b2_staticBody;
        else if(atributes.at("b2BodyType")->AsString() == "kinematic") bodyType = b2_kinematicBody;
        else bodyType = b2_dynamicBody;

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
        else if (atributes.contains("PolygonShape")){
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
        /*SDL_Renderer *renderer = new SDL_Renderer();
        Texture *texture = new Texture();
        addComponent<ecs::RenderTextureComponent>(entity);*/
    }
} 

