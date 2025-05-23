#include "RenderTextureComponent.h"

#include "Texture.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "PhysicsUtils.h"
#include "CameraComponent.h"
#include "GameScene.h"

#include <cmath>

RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderLayer, float scale) 
: RenderComponent(ent, renderLayer),
_texture(texture),
_transform(nullptr),
_defaultRenderLayer(renderLayer),
_scale(scale)
{
    _defaultColor = _color;
}

RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderLayer, float scale, SDL_Rect absCenteredRect)
: RenderTextureComponent(ent, texture, renderLayer, scale)
{
    _absCenteredRect = absCenteredRect;
    _isPortion = true;
}

RenderTextureComponent::RenderTextureComponent(Entity* ent, Texture* texture, int renderLayer, float scale, SDL_Color tint) 
: RenderTextureComponent(ent, texture, renderLayer, scale)
{
    changeColorTint(tint.r, tint.g, tint.b);
    _defaultColor = _color;
}

void RenderTextureComponent::init(){
    _transform = _myEntity->getTransform();
}

void RenderTextureComponent::render() {
    _texture->changeColorTint(_color.r, _color.g, _color.b);
    _texture->changeOpacity(_opacity);
    _texture->render(getRenderRect(), _transform->getRotation());
    _texture->changeColorTint(255,255,255);
    _texture->changeOpacity(255);
}

SDL_Rect RenderTextureComponent::getRenderRect() const
{
    b2Vec2 physicalPosition = b2Vec2_zero;

    if (_isPortion){ // if the rect is a portion of the transform rect the transform position can't be used to render
        physicalPosition = PhysicsConverter::pixel2meter(_absCenteredRect.x, _absCenteredRect.y);
    }
    else {
        physicalPosition = _transform->getPosition();
    }

    //Obtiene la posición de pantalla a partir de la posición física para renderizar la textura
    auto [coordinateX, coordinateY] = _myEntity->getScene().getCamera()->getRenderPos({physicalPosition.x, physicalPosition.y});
    
    //Adapta el rect para que el objeto apareca en el centro de este
    coordinateX -= _scale*_texture->width() / 2;
    coordinateY -= _scale*_texture->height() / 2;

    SDL_Rect dest = build_sdlrect(coordinateX, coordinateY, _texture->width()*_scale, _texture->height()*_scale);

    return dest;
}

void RenderTextureComponent::setNewWidth(float newWidth)
{
    float a_originalWidth = static_cast<float>(_texture->width());
    float a_newScale = newWidth / a_originalWidth;
    setScale(a_newScale);
}

float RenderTextureComponent::getRenderWidth()
{
    SDL_Rect a_rect = getRenderRect();
    return a_rect.w;
}

void RenderTextureComponent::setTexture(Texture* tex){
    _texture = tex;
}