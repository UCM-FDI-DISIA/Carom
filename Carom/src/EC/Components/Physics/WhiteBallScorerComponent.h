#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"

class InventoryManager;
//cambiar todo esto con herencia del componente de Mika
class WhiteBallScorerComponent : public PhysicsComponent{
    InventoryManager* _inventory;

    int _cushions = 0; // rebotes en paredes.
    bool _previouslyHit = false; // para ver si la whiteball ha tocado previamente una colorball.
    const int baseCaromScore = 4;
    const int baseHitScore = 1;

public:
    __CMPID_DECL__(cmp::WHITEBALLSCORER);
    WhiteBallScorerComponent(entity_t ent);

    // funcion q se activa al colisionar con "other".
    void onCollisionEnter(entity_t other, b2Manifold& contactData) override; 

    //setea cushions a 0 y previously hit a false al comienzo del turno
    void refreshOnNewTurn();
};