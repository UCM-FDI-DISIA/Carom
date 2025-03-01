#pragma once
#include "Entity.h"
#include "JSONValue.h"
#include <string>

class ecs::GameScene;
namespace ecs
{
    class JsonEntityParser{
        public:
            static ecs::Entity* Parse(ecs::GameScene& gameScene, std::string JSONfile);
        private:
            static void transformComponent(const JSONObject& atributes, ecs::Entity* entity);
            static void rigidBodyComponent(JSONObject* atributes);
            static void renderTextureComponent(JSONObject* atributes);
        
        template<typename T, typename ...Ts>
            inline static void addComponent(ecs::Entity* e, Ts &&... args) {
                // the component id exists
                static_assert(cmpId<T> < ecs::maxComponentId);
                // create component
                T *c = new T(e, std::forward<Ts>(args)...);
                // install the new component if entity doesn't have one of the type
                if (!e->addComponent<T>(c)) {
                    delete c;
                }
            }
        };
} // namespace ecs

