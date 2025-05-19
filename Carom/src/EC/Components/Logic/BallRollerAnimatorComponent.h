#pragma once
#include "LogicComponent.h"
#include "RenderSpritesheetComponent.h"
#include "RigidBodyComponent.h"
#include <vector>

/// @brief Componente similar a AnimatorComponent, solo que en vez de utilizar una animación para modificar los frames
///        toma en cuenta la velocidad de su rigidbody (se pretende que sea el de una bola con spritesheet)
///        
///        Idealmente ambos animatorcomponents tendrían un padre con las cosas en común
class BallRollerAnimatorComponent : public LogicComponent {
private:
    RenderSpritesheetComponent* _myRenderer;
    /// @brief rigidbody del objeto a animar para obtener su velocidad
    RigidBodyComponent* _myRigidbody;

    /// @brief numero total de frames del spritesheet, se obtiene en init con un get sobre _myRenderer
    int _frameAmount;
    /// @brief indice del frame actual
    int _frameIndex;
    /// @brief La velocidad que equivale a un cambio de frame
    float _frameChangeThreshold;

    /// @brief una vez se cambia de frame a veces queda velocidad sobrante, se guarda 
    ///        para el proximo update para que la animación sea lo mas consistente con
    ///        la velocidad prosible
    float _residualSpeed = .0;
public:
    __CMPID_DECL__(cmp::ANIMATOR);

    BallRollerAnimatorComponent(entity_t ent, float frameChangeThreshold = 1.0);
    ~BallRollerAnimatorComponent() {}

    void init() override;

    /// @brief Obtiene la velocidad en ese momento del _myRigidbody y actualiza los
    ///        frames acorde a todos los valores privados que no son componentes
    void update() override;
};