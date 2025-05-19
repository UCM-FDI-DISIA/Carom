#include "InfoComponent.h"
#include "ecs.h"


// Compenete de los bordes de la mesa
class WallComponent : public InfoComponent{
public:
        WallComponent(entity_t ent) : InfoComponent(ent) {}
    __CMPID_DECL__(cmp::WALL);
};
