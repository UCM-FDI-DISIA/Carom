#pragma once
#include "RenderComponent.h"
#include "Frame.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;

/// @brief Renderiza un objeto en repetición de un punto A a uno B tantas veces como sea posible
///         
///        Se utiliza para renderizar la línea de apuntado
class RenderArrayComponent : public RenderComponent {
private:
    float   _arrayLength;;
    float _scale;

    /// @brief Escala sobre _scaledWidth de la distancia entre cada elemento a renderizar
    float _gapScale;

    /// @brief Se utiliza la longitud (in render) del ancho para tener en cuenta las repeticiones.
    ///        Denotar que sea mod(A,B) = 0, el array se renderiza apuntando a la derecha
    float _scaledWidth;

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

    /// @brief Setea hasta cuan lejos va a renderizar
    /// @param length longitud EN ESCALA RENDER (pixels, not meter)
    void setLength(float length);
};