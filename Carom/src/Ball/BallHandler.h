#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"
#include <vector>

namespace ecs {class CaromScene;}
class BallEffect;

class BallHandler : public ecs::PhysicsComponent
{
private:
    ecs::CaromScene* _scene;
    std::vector<BallEffect*> _effects;

    float _scoreMult = 1;
public:
    BallHandler(ecs::entity_t ent) : ecs::PhysicsComponent(ent) {}
    ~BallHandler() {}

    void init() override;
<<<<<<< Updated upstream
    void onCollisionEnter(ecs::entity_t collision) override; //Se ejecuta cuando ch
    void onBeingTargeted();
    void onStrikeEnd();
=======
    void onCollisionEnter(ecs::entity_t collision) override; //Se ejecuta cuando la bola golpea otra bola
    void onBeingTargeted(); //Se ejecuta cuando esta siendo apuntado por una trayectoria de palo
    void onStrikeEnd(); //Se ejecuta al final de un tiro
>>>>>>> Stashed changes

    inline void addEffect(BallEffect* effect) {_effects.push_back(effect);}
    __CMPID_DECL__(ecs::cmp::BALL_HANDLER);

    void addScore(float points);
    void multScore(float mult);
    inline void setMult(float newMult) {_scoreMult = newMult;}

    std::vector<BallEffect*>& getEffects() {return _effects;}
};