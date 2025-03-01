#include "Component.h"

namespace ecs
{
    Component::Component(Entity* ent) : _myEntity(ent), _enabled(true) {}

    Component::~Component() {}

    void
    Component::setEnabled(bool state) {
        _enabled = state;
    }

    bool
    Component::isEnabled() {
        return _enabled;
    }
}