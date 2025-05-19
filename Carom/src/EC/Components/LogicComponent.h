#pragma once

#include "Component.h"

class Entity;

/// @brief Componente que overridea vacíos todos los métodos base excepto el update
class LogicComponent : public Component
{
public:
    LogicComponent(Entity* ent) : Component(ent) {}
        virtual ~LogicComponent(){}

        void render() override {}
        void handleEvent() override {}
};