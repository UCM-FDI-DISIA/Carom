#pragma once
#include "TextDisplayComponent.h"

class WobblyRenderTextureComponent: public TextDisplayComponent{
    const int VERTICES_BY_WIDTH = 5;
public:
WobblyRenderTextureComponent(Entity* entity, layerId_t renderLayer, float displayScale, 
    std::string initialText, SDL_Color color, std::string key);
    void render() override;
};