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
class SubdivisionEffect;
class EntityGenerator;

class BallHandler : public PhysicsComponent
{
    friend EntityGenerator;

    //friend effects
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
    friend SubdivisionEffect;
private:
    CaromScene* _scene;
    std::array<BallEffect*, effect::_LAST_EFFECT_ID> _effects;
    //ids de los efectos de ballEffect, que se actualiza constantemente. Ahorra calculos en muchos lados al no tener que calcular de clase a id
    std::vector<BallEffect*> _currentEffects;
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

    /// @brief Método genérico para añadir efectos
    /// @tparam T Clase del efecto
    /// @param effect efecto a añadir 
    /// @return true si se añade el efecto, false si no 
    template<typename T>
    bool addEffect(T* effect) {
        return internalAddEffect(effId<T>, effect);
    }
    /// @brief Método genérico para eliminar un efecto de tipo T
    /// @return true si se ha eliminado, false si no
    template<typename T>
    bool removeEffect(){
        return internalRemoveEffect(effId<T>);
    }
    /// @brief Getter genérico de efectos
    /// @return El efecto si lo tiene, nullptr si no
    template<typename T>
    T* getEffect(){
        //como hay lista de componentes y efectos y sus ids pueden coincidir, se puede checkear primero si el efecto no se pasa del array
        assert(effId<T> < effect::_LAST_EFFECT_ID);
        return static_cast<T*>(_effects[effId<T>]);
    }
private:
    bool internalRemoveEffect(effectId_t id, bool deleteCmp = true);
    bool internalAddEffect(effectId_t id, BallEffect* effect, bool initCmp = true);
public:

    void removeAllEffects();
    __CMPID_DECL__(cmp::BALL_HANDLER);

    void addScore(float points); //Se usa para sumar puntos, esta pensado para ser usado por los efectos de bola
    void multScore(float mult); // Se usa para multiplicar la puntuacion total, esta pensado para ser usado por los efectos de bola
    void multRoundScore(float mult); // Se usa para multiplicar la puntuacion de ronda, esta pensado para ser usado por los efectos de bola
    void setMult(float newMult); //Define la intensidad de los efectos de bola

    inline float getMult() {return _mult;}

    std::vector<effectId_t> getEffectsID();
    std::vector<BallEffect*> getCurrentEffects() { return _currentEffects;}
};