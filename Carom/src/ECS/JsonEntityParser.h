#pragma once
#include "Entity.h"
#include "JSONValue.h"
#include <string>
#include <box2d/box2d.h>

class GameScene;

class JsonEntityParser{
    public:
        //instancia una entidad con los componentes de JSONfile en la escena
        static Entity* Parse(GameScene& gameScene, std::string JSONfile, std::string childName = "NONE");

        //añade componentes del JSONfile a la entidad
        static void AddComponentsFromJSON(Entity* e, std::string JSONfile, std::string childName = "NONE");

        // a partir del prefab de una bola, añade los componentes del JSONfile
        static Entity* createEffectBall(GameScene& gameScene, std::string file, std::string childName = "NONE", b2Vec2 pos= {0.f,0.f});

        static Entity* createStick(GameScene& gameScene, std::string file, std::string childName = "NONE", b2Vec2 pos = {0.f,0.f});

        inline static bool FileIsEmpty(std::string JSONfile) { return JSON::ParseFromFile(JSONfile) == NULL; }

        static std::vector<std::string> getBallEffects(entity_t ball);
    private:
        static void transformComponent(const JSONObject& atributes, Entity* entity);
        static void rigidBodyComponent(const JSONObject& atributes, Entity* entity);
        static void renderTextureComponent(const JSONObject& atributes, Entity* entity);
        static void ballHandler(const JSONObject& atributes, Entity* entity);

        //-palos
        static void stickInputComponent(Entity* e);
        static void donutStickEffect(const JSONObject& atributes,Entity* e);
        static void magicWandStickEffect(const JSONObject& atributes,Entity* e);
        static void boxingGloveStickEffect(const JSONObject& atributes,Entity* e);
        static void grenadeLauncherStickEffect(const JSONObject& atributes,Entity* e);
        
    
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

