#include "Component.h"

namespace ecs
{
    Component::Component(Entity* ent) : _myEntity(ent), _isEnable(true) {}

    Component::~Component() {}

    void
    Component::setEnabled(bool state) {
        _isEnable = state;
    }

    bool
    Component::isEnabled() {
        return _isEnable;
    }
}