#pragma once
#include "RenderComponent.h"
#include "Frame.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;

class RenderArrayComponent : public RenderComponent {
private:
    float   _arrayLength, 
            _scale,
            _gapScale,
            _scaledHeight;

    Texture* _texture;
    ITransform* _myTransform;

    SDL_Rect getSectionRenderRect(float currentLength) const;

public:
    __CMPID_DECL__(cmp::RENDER_ARRAY);

    RenderArrayComponent(entity_t ent, Texture* tex, layerId_t renderLayer, float scale, float gapScale = 0.5);
    ~RenderArrayComponent() {}

    void init() override;
    void render() override;

    SDL_Rect getRenderRect() const override;

    void setLength(float length);
};