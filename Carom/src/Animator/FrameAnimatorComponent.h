#pragma once
#include "LogicComponent.h"
#include "Frame.h"
#include <vector>

class RenderTextureComponent;

namespace ecs{
    class FrameAnimatorComponent : public LogicComponent
    {
    public:
        FrameAnimatorComponent(entity_t ent, Frame* startingFrame);
        ~FrameAnimatorComponent() {}

        void init() override;
        void update() override;

        void applyExitCase();

        enum ExitCase {
            DISABLE,
            KILL_MYSELF,
            LOOP
        };

    private:
        void enableFrame();

        Uint32 _frameStartTimestamp;
        Frame* _currentFrame;
        Frame* _startingFrame;
        RenderTextureComponent* _renderTextureComponent;

        ExitCase _exitCase;
    };
}