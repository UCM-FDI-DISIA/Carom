#pragma once
#include "LogicComponent.h"
#include "Frame.h"
#include "Animation.h"
#include "RenderSpritesheetComponent.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;
struct SDL_Rect;

/// @brief Componente encargado de cambiar el frame de renderspritesheetcomponent (es dependiente de este otro)
class AnimatorComponent : public LogicComponent {
private:
    RenderSpritesheetComponent* _myRenderer;
    Animation* _animation;

    /// @brief El indice que del frame que está activo en la animación en este momento
    int _frameIndex;

    /// @brief timestamp de cuando comenzó el último frame
    Uint32 _frameStartTimestamp;

    /// @brief Es llamado cuando se agota el tiempo del último frame de la aniamación
    /// @param animType Se debe pasar el animType de _animation
    void animationEnd(Animation::AnimationType animType);

    /// @brief Reinicia la animación al primer frame (índice 0)
    void restartAnimation();
public:
    __CMPID_DECL__(cmp::ANIMATOR);

    /// @brief
    /// @param ent 
    /// @param anim La animación suele pasarse mediante sdlutils().animations().at("id_de_animacion")
    AnimatorComponent(entity_t ent,  Animation* anim);
    ~AnimatorComponent() {}

    void init() override;
    void update() override;

    /// @brief Cambia la animación por newAnim
    /// @param newAnim 
    void setAnimation(Animation* newAnim);
};