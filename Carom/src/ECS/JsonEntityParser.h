#pragma once
#include "Entity.h"
#include "JSONValue.h"
#include "GameScene.h"
#include <string>

class JsonEntityParser{
public:
    static ecs::Entity* Parse(ecs::GameScene& gameScene, std::string JSONfile);
private:
    void transformComponent(const JSONObject& atributes);
    void rigidBodyComponent(JSONObject* atributes);
    void renderTextureComponent(JSONObject* atributes);

};