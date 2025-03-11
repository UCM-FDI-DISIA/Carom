#include "JsonEntityParser.h"
#include "JSON.h"
#include "Vector2D.h"

#include "TransformComponent.h"
#include "RigidBodyComponent.h"

#include <iostream>

namespace ecs
{
    Entity* JsonEntityParser::Parse(GameScene& gameScene,std::string file){

        Entity* entity = new Entity(gameScene);
        JSONValue* entityElements = JSON::ParseFromFile(file);
        //std::cout<<JSON::Stringify(entityElements);
    
        for(auto element : entityElements->AsArray()){
            if(element->Child("componentName")->AsString() == "TransformComponent"){
                JSONObject atributes = element->Child("atributes")->AsObject();
                transformComponent(atributes, entity);
            }
            else if(element->Child("componentName")->AsString() == "RigidBodyComponent"){
                JSONObject atributes = element->Child("atributes")->AsObject();
                rigidBodyComponent(atributes, entity);
            }
            else if(element->Child("componentName")->AsString() == "RenderTextureComponent"){
            }
        }
       return nullptr;
    }
    
    void JsonEntityParser::transformComponent(const JSONObject& atributes, Entity* entity){
        b2Vec2 position(atributes.at("x")->AsNumber(), atributes.at("y")->AsNumber());
        addComponent<ecs::TransformComponent>(entity, position);
    }

    void JsonEntityParser::rigidBodyComponent(const JSONObject& atributes, Entity* entity){
        
        Shape* shape;
        //escoge la forma del rigidbody
        if(atributes.at("CircleShape")->IsObject()){
            shape = new CircleShape(atributes.at("CircleShape")->Child("radius")->AsNumber());//crea un circulo
        }
        else if (atributes.at("CapsuleShape")->IsObject()){
            JSONValue* capsule = atributes.at("CapsuleShape");
            b2Vec2 firstCenter(capsule->Child("firstCenter")->Child("x")->AsNumber(),capsule->Child("firstCenter")->Child("y")->AsNumber()),
                   secondCenter(capsule->Child("secondCenter")->Child("x")->AsNumber(),capsule->Child("secondCenter")->Child("y")->AsNumber());
            shape = new CapsuleShape(capsule->Child("radius")->AsNumber(),firstCenter, secondCenter);//crea una capsula
        }
        else if (atributes.at("PolygonShape")->IsObject()){
            JSONValue* poligon = atributes.at("PolygonShape");
            int size = poligon->Child("size")->AsNumber();
            float radius = poligon->Child("radius")->AsNumber();
            float temp1=0, temp2=0;
            b2Vec2 vertex[100];
            for(int i = 0; i < size; i++){
                temp1 = atributes.at("PolygonShape")->Child("vertex")->AsArray()[i]->Child("x")->AsNumber();
                temp2 = poligon->Child("vertex")->AsArray()[i]->Child("y")->AsNumber();
                vertex[i] = {temp1, temp2};
            }
            shape = new PolygonShape(vertex, size, radius);//crea un poligono con size vertices
        }
        else if(atributes.at("RectangleShape")->IsObject()){
            float sizex = atributes.at("RectangleShape")->Child("sizex")->AsNumber(),
                  sizey = atributes.at("RectangleShape")->Child("sizey")->AsNumber();
            shape = new PolygonShape(sizex, sizey);//crea un rectangulo
        }
        else if(atributes.at("SquareShape")->IsObject()){
            shape = new PolygonShape(atributes.at("SquareShape")->Child("side")->AsNumber());//crea un cuardado
        }
        
        b2BodyType bodyType;
        //escoge el tipo de body type
        if(atributes.at("b2BodyType")->AsString() == "static") bodyType = b2_staticBody;
        else if(atributes.at("b2BodyType")->AsString() == "kinematic") bodyType = b2_kinematicBody;
        else bodyType = b2_dynamicBody;

        b2Vec2 pos(atributes.at("pos")->Child("x")->AsNumber(), atributes.at("pos")->Child("y")->AsNumber());
        
        float density = atributes.at("density")->AsNumber(),
              friction = atributes.at("friction")->AsNumber(),
              restitution = atributes.at("restitution")->AsNumber();
        RigidBodyComponent* a = new RigidBodyComponent(entity, pos, bodyType, shape, density, friction, restitution); 
        addComponent<ecs::RigidBodyComponent>(entity, pos, bodyType, shape, density, friction, restitution);
    }
} // namespace ecs

