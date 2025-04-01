#include "Component.h"
#include "ecs.h"

class WallComponent : public Component{
public:
    __CMPID_DECL__(cmp::WALL);
};