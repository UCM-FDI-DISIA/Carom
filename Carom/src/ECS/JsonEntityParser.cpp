#include "JsonEntityParser.h"
#include "JSON.h"
#include "TransformComponent.h"

#include <iostream>

ecs::Entity* JsonEntityParser::Parse(ecs::GameScene& gameScene,std::string file){

    ecs::Entity* entity = new ecs::Entity(gameScene);
    JSONValue* entityElements = JSON::ParseFromFile(file);
    std::cout<<JSON::Stringify(entityElements);

    for(auto element : entityElements->AsArray()){
        if(element->Child("componentName")->AsString() == "TransformComponent"){
            JSONObject atributes = element->Child("atributes")->AsObject();
            transformComponent(atributes, entity);
        }
        else if(element->Child("componentName")->AsString() == "RigidBodyComponent"){

        }
        else if(element->Child("componentName")->AsString() == "RenderTextureComponent"){

        }
    }
   return nullptr;
}

void JsonEntityParser::transformComponent(const JSONObject& atributes,  ecs::Entity* entity){
    
    ecs::TransformComponent component = new ecs::TransformComponent(entity, {atributes.at("x"),atributes.at("y")});
}