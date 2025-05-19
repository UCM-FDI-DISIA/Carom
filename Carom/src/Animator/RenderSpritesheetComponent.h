#pragma once
#include "RenderComponent.h"
#include "Frame.h"
#include <vector>

class Camera;
class ITransform;
struct Animation;

/// @brief Componente de render. Renderiza un spritesheet en el frame que se le indique
class RenderSpritesheetComponent : public RenderComponent {
private:
    /// @brief Numero de filas y columnas del spritesheet
    int _rows, _cols;
    /// @brief Dimensiones de cada frame
    int _width, _height;
    /// @brief Frame al que se está apuntando
    int _xOriginFrame, _yOriginFrame, _currentFrame;

    float _scale;

    Texture* _texture;
    ITransform* _transform;

public:
    __CMPID_DECL__(cmp::RENDER_SPRITESHEET);

    /// @brief Si rows y cols no es como mínimo 1 salta un error. Si frame no está dentro de los frames
    ///        válidos (rows*cols) salta un error.
    /// @param ent 
    /// @param  
    /// @param renderLayer 
    /// @param scale 
    /// @param rows 
    /// @param cols 
    /// @param frame 
    RenderSpritesheetComponent(entity_t ent,  Texture*, layerId_t renderLayer, 
        float scale, int rows = 1, int cols = 1, int frame = 0);
    ~RenderSpritesheetComponent() {}

    void init() override;
    /// @brief Renderiza el frame actual según _xOriginFrame e _yOriginFrame
    void render() override;
    void setTexture(Texture* t) { _texture = t; }
    inline Texture* getTexture() const { return _texture; }

    /// @brief Devuelve el rect equivalente a como se debe renderizar en pantalla
    /// @return 
    SDL_Rect getRenderRect() const override;
    /// @brief Cambia _xOriginFrame e _yOriginFrame al frame equivalente
    /// @param frame entre 0 y _cols*_rows - 1
    void setFrame(int frame);
    void setNewWidth(float newWidth);

    inline void setScale(float s) {_scale = s;}
    inline int getFrameAmount() const { return _rows * _cols; }
    inline int getCurrentFrame() const { return _currentFrame; } 
    inline float getRenderWidth() {    
        SDL_Rect a_rect = getRenderRect();
        return a_rect.w;
    }
};