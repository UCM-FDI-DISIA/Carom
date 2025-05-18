#pragma once
#include "TextDisplayComponent.h"


//Hereda de TextDisplayComponent, y lo único que hace es sobreescribir el método render para poder renderizar el texto con vértices de SDL. Con esto, se puede simular un shader de movimiento ya que en cada iteración los vértices se van moviendo dando ese efecto de ola.
class WobblyRenderTextureComponent: public TextDisplayComponent{
    const int VERTICES_BY_WIDTH = 12;
    float _speed = 7;
    float _height = 20;
public:
WobblyRenderTextureComponent(Entity* entity, layerId_t renderLayer, float displayScale, 
    std::string initialText, SDL_Color color, std::string key);
    void render() override;
};