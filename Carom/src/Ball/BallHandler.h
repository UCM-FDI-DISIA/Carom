#pragma once
#include "PhysicsComponent.h"
#include "ecs.h"
#include <vector>
#include <array>

class CaromScene;
class BallEffect;
class PetanqueEffect;
class CristalEffect;
class X2Effect;
class BowlingEffect;
class AbacusEffect;
class PokeballEffect;
class ExplosiveEffect;
class FrictionMultiplierEffect;
class PopToOppositeSideEffect;

class BallHandler : public PhysicsComponent
{
    friend BallEffect;
    friend PetanqueEffect;
    friend CristalEffect;
    friend X2Effect;
    friend BowlingEffect;
    friend AbacusEffect;
    friend PokeballEffect;
    friend ExplosiveEffect;
    friend FrictionMultiplierEffect;
    friend PopToOppositeSideEffect;
private:
    CaromScene* _scene;
    std::array<BallEffect*, effect::_LAST_EFFECT_ID> _effects;
    //ids de los efectos de ballEffect, que se actualiza constantemente. Ahorra calculos en muchos lados al no tener que calcular de clase a id
    std::vector<effectId_t> _effectIds;
    static constexpr int EFFECTS_LIMIT = 3;

    float _mult = 1;
    bool _breakHit = false; //Se usa para romper con el bucle de efectos
public:
    void breakHit() {_breakHit = true;} //Se usa para romper con el bucle de efectos
    BallHandler(entity_t ent) : PhysicsComponent(ent) {}
    ~BallHandler() {}

    void init() override;
    void onCollisionEnter(entity_t collision, b2Manifold& contactData) override; //Se ejecuta cuando la bola golpea otra bola
    void onBeingTargeted(); //Se ejecuta cuando esta siendo apuntado por una trayectoria de palo
    void onStrikeEnd(); //Se ejecuta al final de un tiro

    bool addEffect(effectId_t effect);
    bool removeEffect(effectId_t effect);
    void removeAllEffects();
    __CMPID_DECL__(cmp::BALL_HANDLER);

    void addScore(float points); //Se usa para sumar puntos, esta pensado para ser usado por los efectos de bola
    void multScore(float mult); // Se usa para multiplicar la puntuacion total, esta pensado para ser usado por los efectos de bola
    void multRoundScore(float mult); // Se usa para multiplicar la puntuacion de ronda, esta pensado para ser usado por los efectos de bola
    void setMult(float newMult); //Define la intensidad de los efectos de bola

    inline float getMult() {return _mult;}

    inline std::vector<effectId_t> getEffectsID() { return _effectIds;}
};