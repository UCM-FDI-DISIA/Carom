#pragma once
#include "Entity.h"
#include "JSONValue.h"
#include <string>

class ecs::GameScene;

class JsonEntityParser{
public:
    static ecs::Entity* Parse(ecs::GameScene& gameScene, std::string JSONfile);
private:
    static void transformComponent(const JSONObject& atributes, ecs::Entity* entity);
    static void rigidBodyComponent(JSONObject* atributes);
    static void renderTextureComponent(JSONObject* atributes);

};