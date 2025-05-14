#pragma once
#include "ecs.h"

class CameraComponent;

class Component
{
protected:
    entity_t _myEntity;
    bool _isEnable;
public:
    Component(entity_t ent);
    virtual ~Component() = 0;

    inline virtual void setEntity(entity_t other) { _myEntity = other; }
    
    virtual void init() = 0;

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void handleEvent() = 0;

    virtual void setEnabled(bool state);

    inline entity_t getEntity() {return _myEntity;}

    bool isEnabled();
};
