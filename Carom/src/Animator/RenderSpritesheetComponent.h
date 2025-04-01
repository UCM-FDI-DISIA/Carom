#pragma once
#include "RenderComponent.h"
#include "Frame.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;

class RenderSpritesheetComponent : public RenderComponent {
private:
    int cols, rows;
    int frame;

    float _scale;

    Texture* _texture;
    ITransform* _transform;

public:
    __CMPID_DECL__(cmp::RENDER_SPRITESHEET);

    int renderOrder;

    RenderSpritesheetComponent(entity_t ent,  Texture*, int renderOrder, 
        float scale, int rows = 1, int cols = 1, int frame = 0);
    ~RenderSpritesheetComponent() {}

    void init() override;
    void render(Camera*) override;
};