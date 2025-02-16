#include <box2D/box2D.h>
#include <unordered_map>

#include "Singleton.h"
#include "Entity.h"
#include "ScenesManager.h"

namespace std {
    template <>
    struct hash<b2BodyId> {
        // Funcion hash para poder usar bodyId como key de un map
        size_t operator()(const b2BodyId& bodyId) const {
            size_t hash_value = 0;

            // Hash de index1 (int32_t)
            hash_value ^= std::hash<int32_t>()(bodyId.index1) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);

            // Hash de world0 (uint16_t)
            hash_value ^= std::hash<uint16_t>()(bodyId.world0) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);

            // Hash de generation (uint16_t)
            hash_value ^= std::hash<uint16_t>()(bodyId.generation) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);

            return hash_value;
        }
    };
}

bool operator==(const b2BodyId& first, const b2BodyId& second) {
    return (first.index1 == second.index1) && 
           (first.world0 == second.world0) && 
           (first.generation == second.generation);
}

class B2Manager : public Singleton<B2Manager> {
private:
    friend Singleton<B2Manager>;
    B2Manager();
    virtual ~B2Manager();

    // en caso de necesitar acceder a la entidad de un componente con el que se ha colisionado
    // se puede usar este mapa para acceder
    std::unordered_map<b2BodyId, ecs::Entity*> _bodyEntityMap;

    b2WorldId _worldId;

    bool init();

    std::tuple<b2BodyId&, b2ShapeDef&> generateBodyAndShape(ecs::Entity* entity, b2BodyType bodyType, float density, float friction, float restitution);

    float _timeStep;
    int _subStepCount;

protected:

    void stepWorld();

    // esto está aquí para que al cambiar de escena si se requiere ScenesManager reinicie el mundo
    // al cambiar entre escenas
    friend ScenesManager;
    void reloadWorld();

public:

    b2BodyId addRigidbody(ecs::Entity* entity, b2BodyType bodyType, const b2Circle& circle, float density, float friction, float restitution);
    b2BodyId addRigidbody(ecs::Entity* entity, b2BodyType bodyType, const b2Polygon& polygon, float density, float friction, float restitution);
    b2BodyId addRigidbody(ecs::Entity* entity, b2BodyType bodyType, const b2Capsule& capsule, float density, float friction, float restitution);

    void removeBody(const b2BodyId& id);

    ecs::Entity* getEntity(const b2BodyId& id) const;
};