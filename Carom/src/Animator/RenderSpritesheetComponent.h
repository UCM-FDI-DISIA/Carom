#pragma once
#include "RenderComponent.h"
#include "Frame.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;

class RenderSpritesheetComponent : public RenderComponent {
private:
    int _rows, _cols,
        _width, _height, 
        _xOriginFrame, _yOriginFrame;

    float _scale;

    Texture* _texture;
    ITransform* _transform;

public:
    __CMPID_DECL__(cmp::RENDER_SPRITESHEET);

    RenderSpritesheetComponent(entity_t ent,  Texture*, layerId_t renderLayer, 
        float scale, int rows = 1, int cols = 1, int frame = 0);
    ~RenderSpritesheetComponent() {}

    void init() override;
    void render() override;

    SDL_Rect getRenderRect() const override;
    void setFrame(int frame);
};