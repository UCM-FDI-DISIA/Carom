#pragma once
#include "LogicComponent.h"
#include "Frame.h"
#include "Animation.h"
#include "AnimatorComponent.h"
#include "RenderSpritesheetComponent.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;

class AnimatorComponent : public LogicComponent {
private:
    RenderSpritesheetComponent* _myRenderer;
    Animation* _animation;
    int _frameIndex;
    Uint32 _frameStartTimestamp;

    void animationEnd(Animation::AnimationType);
public:
    __CMPID_DECL__(cmp::RENDER_SPRITESHEET);

    AnimatorComponent(entity_t ent,  Animation* anim);
    ~AnimatorComponent() {}

    void init() override;
    void update() override;

    void restartAnimation();
};