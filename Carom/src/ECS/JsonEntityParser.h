#pragma once
#include "Entity.h"
#include "JSONValue.h"
#include <string>


class GameScene;

class JsonEntityParser{
    public:
        static Entity* Parse(GameScene& gameScene, std::string JSONfile);
    private:
        static void transformComponent(const JSONObject& atributes, Entity* entity);
        static void rigidBodyComponent(const JSONObject& atributes, Entity* entity);
        static void renderTextureComponent(const JSONObject& atributes, Entity* entity);

        //ball efects
        static void ballHandler(const JSONObject& atributes, Entity* entity);
        
    
        template<typename T, typename ...Ts>
            inline static void addComponent(Entity* e, Ts &&... args) {
                // the component id exists
                static_assert(cmpId<T> <maxComponentId);
                // create component
                T *c = new T(e, std::forward<Ts>(args)...);
                // install the new component if entity doesn't have one of the type
                if (!e->addComponent<T>(c)) {
                    delete c;
                }
            }
        };

