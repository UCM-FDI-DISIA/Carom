#pragma once

#include "ecs.h"
#include "RenderComponent.h"
#include "ITransform.h"
#include "SDL.h"

class SDL_Rect;
class Texture;

class TweenComponent;
    
/// @brief Componente de render de todos los objetos con textura
class RenderTextureComponent : public RenderComponent {
    friend TweenComponent;
protected:
    Texture* _texture = nullptr;
    ITransform* _transform;
    float _scale; // scale de la textura (no su physical body)
    bool _isPortion = false; // If the rect is a portion of a rect

    SDL_Rect _absCenteredRect;

    // See ecs.h for layers enum
    layerId_t _defaultRenderLayer;
public:
    __CMPID_DECL__(cmp::RENDER_TEXTURE);

    /// @brief Constructora del componente de renderizado con texturas
    /// @param texture la textura  
    /// @param renderLayer la capa que representa la profundidad de renderizado
    /// @param scale La escala de la textura
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale);


    /// @brief Constructora del componente de renderizado con texturas
    /// @param texture la textura  
    /// @param renderLayer la capa que representa la profundidad de renderizado
    /// @param scale La escala de la textura
    /// @param absCenteredRect 
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Rect absCenteredRect);


    /// @brief Constructora del componente de renderizado con texturas
    /// @param texture la textura  
    /// @param renderLayer la capa que representa la profundidad de renderizado
    /// @param scale La escala de la textura
    /// @param tint EL color del que se tiñe la textura 
    RenderTextureComponent(Entity*, Texture*, int renderLayer, float scale, SDL_Color tint);
    ~RenderTextureComponent() {};

    virtual void render() override;
    void init() override;
    Texture* getTexture() {return _texture;};
    void setTexture(Texture* tex);

    inline float getScale(){return _scale;}
    inline void setScale(float s) {_scale = s;}
    
    SDL_Rect getRenderRect() const override;
    float getRenderWidth();
    void setNewWidth(float newWidth);
};