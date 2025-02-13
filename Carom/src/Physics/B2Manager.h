#include <box2D/box2D.h>
#include "Singleton.h"
#include <unordered_map>
#include "Entity.h"

namespace std {
    template <>
    struct hash<b2BodyId> {
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

class B2Manager : public Singleton<B2Manager> {
private:
    friend Singleton<B2Manager>;
    B2Manager();
    virtual ~B2Manager();

    bool init();

    // en caso de necesitar acceder a la entidad de un componente con el que se ha colisionado
    // se puede usar este mapa para acceder
    std::unordered_map<b2BodyId, ecs::Entity*> _bodyEntityMap;

    b2WorldId _worldId;

public:
    void addBody();
    void removeBody();

    ecs::Entity* getEntity();
};