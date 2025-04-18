#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"
#include <vector>

class CaromScene;
class BallEffect;

class BallHandler : public PhysicsComponent
{
private:
    CaromScene* _scene;
    std::vector<BallEffect*> _effects;
    static constexpr int EFFECTS_LIMIT = 3;

    float _mult = 1;
public:
    BallHandler(entity_t ent) : PhysicsComponent(ent) {}
    ~BallHandler() {}

    void init() override;
    void onCollisionEnter(entity_t collision, b2Manifold& contactData) override; //Se ejecuta cuando la bola golpea otra bola
    void onBeingTargeted(); //Se ejecuta cuando esta siendo apuntado por una trayectoria de palo
    void onStrikeEnd(); //Se ejecuta al final de un tiro

    bool addEffect(BallEffect* effect);
    void removeAllEffects();
    __CMPID_DECL__(cmp::BALL_HANDLER);

    void addScore(float points); //Se usa para sumar puntos, esta pensado para ser usado por los efectos de bola
    void multScore(float mult); // Se usa para multiplicar la puntuacion total, esta pensado para ser usado por los efectos de bola
    void multRoundScore(float mult); // Se usa para multiplicar la puntuacion de ronda, esta pensado para ser usado por los efectos de bola
    void setMult(float newMult); //Define la intensidad de los efectos de bola

    std::vector<BallEffect*>& getEffects() {return _effects;}
    inline float getMult() {return _mult;}
};