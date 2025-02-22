#include "JsonEntityParser.h"
#include "JSON.h"
#include <iostream>

ecs::Entity* JsonEntityParser::Parse(ecs::GameScene& gameScene,std::string file){

    ecs::Entity* entity = new ecs::Entity(gameScene);
    JSONValue* entityElements = JSON::ParseFromFile(file);
    std::cout<<JSON::Stringify(entityElements);

    for(auto element : entityElements->AsArray()){
        if(element->Child("componentName")->AsString() == "TransformComponent"){
            transformComponent(element->Child("atributes")->AsObject());
        }
        else if(element->Child("componentName")->AsString() == "RigidBodyComponent"){

        }
        else if(element->Child("componentName")->AsString() == "RenderTextureComponent"){

        }
    }
   return nullptr;
}