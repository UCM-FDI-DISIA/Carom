#include "Component.h"

namespace ecs
{
Component::Component(Entity* ent) : _myEntity(ent), _active(true) {}

Component::~Component() {}

void
Component::setEnable(bool state) {
    _active = state;
}

bool
Component::isEnable() {
    return _active;
}
}