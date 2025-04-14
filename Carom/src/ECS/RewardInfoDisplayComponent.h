#pragma once

#include <string>
#include <vector>

#include "RenderTextureComponent.h"


class RewardInfoDisplayComponent : public RenderTextureComponent {
public:
    struct Body {
        std::string text;
        std::string font;
        SDL_Color color;
    };

protected:
    Body _title; // su textura es _texture
    
    Body _rewardName;
    Texture* _rewardNameTexture;

    Body _rewardType;
    Texture* _rewardTypeTexture;
    
    Body _rewardDescription;
    Texture* _rewardDescTexture;
    Uint32 _wrapLength;

    int _offsetX, _offsetY;
    
    void generateTextures();

public:
    /// @brief Constructor del componente para mostrar las recompensas en la mesa de Pool
    /// @param entity La entidad a la que pertenece
    /// @param scale la escala del rect donde se crea el texto
    /// @param title Texto, fuente y color para el renderizado del título
    /// @param rewardName, rewardType, rewardDescription Info de la recompensa (textos, fuentes y colores)
    /// @param wrapLength Longitud de línea
    RewardInfoDisplayComponent(Entity* entity, layerId_t renderLayer, float scale, 
        Body title, Body rewardName, Body rewardType, Body rewardDescription, 
        Uint32 wrapLength = 0, int offsetX = 0, int offsetY = 0);


    void render() override;

    SDL_Rect getRenderRect(Texture* t, int offset = 0) const;
};


