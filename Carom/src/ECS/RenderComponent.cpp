#include "RenderComponent.h"
#include "Entity.h"
#include "GameScene.h"

RenderComponent::RenderComponent(Entity* ent, layerId_t renderLayer)
: Component(ent), 
_renderLayer(renderLayer),
_defaultRenderLayer(renderLayer) {

    _defaultColor = _color;
}

void RenderComponent::setRenderLayer(layerId_t layer) {    
    _renderLayer = layer;
    _myEntity->getScene().sortRenderOrder();
}

void RenderComponent::resetRenderLayer()
{
    _renderLayer = _defaultRenderLayer;
    _myEntity->getScene().sortRenderOrder();
}

void RenderComponent::changeColorTint(int r, int g, int b){
    _color.r = r;
    _color.g = g;
    _color.b = b;
}

void RenderComponent::resetColorTint(){
    // _color = _defaultColor;
    _color.r = _defaultColor.r;
    _color.g = _defaultColor.g;
    _color.b = _defaultColor.b;
}