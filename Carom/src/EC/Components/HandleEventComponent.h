#pragma once
#include "Component.h"
class Entity;

/// @brief Componente que overridea a vacío todo excepto manejar eventos
class HandleEventComponent : public Component
{
public:
    HandleEventComponent(Entity* ent) : Component(ent) {}
    virtual ~HandleEventComponent(){}

    void update() override {}
    void render() override {}
};
