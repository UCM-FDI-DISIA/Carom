#include "B2Manager.h"
#include <functional>



B2Manager::B2Manager() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = {0.0f, 0.0f};
    _worldId = b2CreateWorld(&worldDef);
}