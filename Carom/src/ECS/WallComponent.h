#include "InfoComponent.h"
#include "ecs.h"

class WallComponent : public InfoComponent{
public:
        WallComponent(entity_t ent) : InfoComponent(ent) {}
    __CMPID_DECL__(cmp::WALL);
};
