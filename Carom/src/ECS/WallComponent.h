#include "Component.h"
#include "ecs.h"

namespace ecs{
    class WallComponent : public Component{
public:
    __CMPID_DECL__(cmp::WALL);
    };
}
